#pragma once

#include <string>
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

	Component* MakeComponent(std::string name, GameObject* parent);
}