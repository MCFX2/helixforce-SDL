#include "ComponentRegistry.h"

#include <unordered_map>

static std::unordered_map<std::string, std::function<Component*(GameObject*)>>* Component_Dict;

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
}
