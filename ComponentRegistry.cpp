#include "ComponentRegistry.h"

#include <unordered_map>

//this maps a component label string to a static constructor for it
static std::unordered_map<std::string, std::function<Component*(GameObject*)>>* Component_Dict;

//this maps a component label string to a map which in turn maps property label strings to setters for those properties
//(i dont recommend trying to understand this)
static std::unordered_map <std::string, std::unordered_map<std::string, std::function<void(Component*, std::istringstream&)>>> prop_map;

namespace ComponentRegistry
{
	RegisterComponent::RegisterComponent(std::string name, std::function<Component * (GameObject*)> create_func)
	{ //HACKHACK: This is a workaround for a race condition
		//basically, Component_Dict may be uninitialized at this point so we have to "force" it to be
		//initialized by initializing it statically inside this function and maintaining a pointer to it.
		static std::unordered_map<std::string, std::function<Component * (GameObject*)>> Comp_dict;
		if (!Component_Dict) Component_Dict = &Comp_dict;
		//END HACKHACK
		Component_Dict->emplace(name, create_func);
	}

	Component* MakeComponent(std::string name, GameObject* parent)
	{
		auto fn = Component_Dict->find(name);
		if (fn == Component_Dict->end())
		{
			return nullptr;
		}
		return std::invoke(fn->second, parent);
	}

	RegisterProperty::RegisterProperty(std::string component_name, std::string property_name,
		std::function<void(Component*, std::istringstream&)> set_func)
	{ //first resolve component name to property list
		auto prop_list_search = prop_map.find(component_name);
		if (prop_list_search == prop_map.end())
		{ //no list found, make a new one
			std::unordered_map<std::string, std::function<void(Component*, std::istringstream&)>> n_map;
			prop_map.emplace(component_name, n_map);
			//fix the iterator and continue
			prop_list_search = prop_map.find(component_name);
		}
		prop_list_search->second.emplace(property_name, set_func);
	}
}
