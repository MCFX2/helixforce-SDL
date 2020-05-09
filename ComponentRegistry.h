#pragma once

#include <string>
#include <sstream>
#include <functional>

class Component;
class GameObject;

//this registers the component to the component registry, given a string tag to identify the type by,
//and the type name itself.
//example: REGISTER_COMPONENT("Sprite", Sprite);
#define REGISTER_COMPONENT(TAG, TYPE) static ComponentRegistry::RegisterComponent COMPONENT_REGISTERED\
	(##TAG##,[](GameObject* a){return new TYPE##(a); })

namespace ComponentRegistry
{
	struct RegisterComponent
	{
		RegisterComponent(std::string name, std::function<Component * (GameObject*)> create_func);
	};

	//do not try to understand how this code works, you will be sad
	struct RegisterProperty
	{
		RegisterProperty(std::string component_name, std::string property_name,
			std::function<void(Component*, std::istringstream&)> set_func);
	};

	Component* MakeComponent(std::string name, GameObject* parent);

	//need some kind of way to actually use the property table, figure this out later
}
