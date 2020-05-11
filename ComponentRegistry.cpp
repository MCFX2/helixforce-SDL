#include "ComponentRegistry.h"

#include <unordered_map>
#include <algorithm>

//this maps a component label string to a static constructor for it
static std::unordered_map<std::string, std::function<Component*(GameObject*)>>* Component_Dict;

//this maps a component label string to a map which in turn maps property label strings to setters for those properties
//(i dont recommend trying to understand this)
static std::unordered_map <std::string, std::unordered_map<std::string, ComponentRegistry::Property_Setter_Func>>* Property_Dict;

namespace ComponentRegistry
{
	RegisterComponent::RegisterComponent(std::string name, std::function<Component * (GameObject*)> create_func)
		: tag_(name)
	{ //HACKHACK: This is a workaround for a race condition
		//basically, Component_Dict may be uninitialized at this point so we have to "force" it to be
		//initialized by initializing it statically inside this function and maintaining a pointer to it.
		static std::unordered_map<std::string, std::function<Component * (GameObject*)>> Comp_dict;
		if (!Component_Dict) Component_Dict = &Comp_dict;
		//END HACKHACK
		//make tag all upper-case
		std::transform(tag_.begin(), tag_.end(), tag_.begin(), std::toupper);
		Component_Dict->emplace(tag_, create_func);
	}

	Component* MakeComponent(std::string name, GameObject* parent)
	{
		std::transform(name.begin(), name.end(), name.begin(), std::toupper);
		auto fn = Component_Dict->find(name);
		if (fn == Component_Dict->end())
		{
			return nullptr;
		}
		return std::invoke(fn->second, parent);
	}

	RegisterProperty::RegisterProperty(RegisterComponent& component, std::string property_name,
		Property_Setter_Func set_func)
	{ //first resolve component name to property list
		//See HACKHACK in RegisterComponent::RegisterComponent() above.
		static std::unordered_map<std::string, std::unordered_map<std::string, Property_Setter_Func>> prop_map;
		if (!Property_Dict) Property_Dict = &prop_map;
		//End HACKHACK
		auto prop_list_search = prop_map.find(component.tag_);
		if (prop_list_search == prop_map.end())
		{ //no list found, make a new one
			std::unordered_map<std::string, Property_Setter_Func> n_map;
			prop_map.emplace(component.tag_, n_map);
			//fix the iterator and continue
			prop_list_search = prop_map.find(component.tag_);
		}
		std::transform(property_name.begin(), property_name.end(), property_name.begin(), std::toupper);
		prop_list_search->second.emplace(property_name, set_func);
	}

	Property_Setter_Func SetProperty(std::string component_name, std::string prop_tag)
	{
		auto comp_prop_list = Property_Dict->find(component_name);
		if (comp_prop_list == Property_Dict->end())
		{ //component not found in dict
			return nullptr;
		}
		auto prop = comp_prop_list->second.find(prop_tag);
		if (prop == comp_prop_list->second.end())
		{ //property not found in dict
			return nullptr;
		}
		return prop->second;
	}
}
