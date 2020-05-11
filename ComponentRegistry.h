#pragma once

#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>

class Component;
class GameObject;

//this registers the component to the component registry, given a string tag to identify the type by,
//and the type name itself.
//example: REGISTER_COMPONENT("Sprite", Sprite);
#define REGISTER_COMPONENT(TAG, TYPE) static ComponentRegistry::RegisterComponent COMPONENT_##TYPE##_REGISTERED\
	(##TAG##,[](GameObject* a){return new TYPE##(a); })

//this registers a property to an already-registered component.
//Simple properties are just dumb values set after object construction. Do not use this for properties
//that require specific code to be run apart from just... setting the value.
//example (given above): REGISTER_SIMPLE_PROPERTY(Sprite, "Offset", offset);
#define REGISTER_SIMPLE_PROPERTY(TYPE, TAG, PROPERTY) static ComponentRegistry::RegisterProperty PROP_##PROPERTY##_SIMPLE_REGISTERED\
(COMPONENT_##TYPE##_REGISTERED,##TAG##,[](Component* a, std::istringstream& b){##TYPE##* c = static_cast<##TYPE##*>(a);b>>c->##PROPERTY##;})

//this is like REGISTER_SIMPLE_PROPERTY, but it instead requires you to supply your own setter function.
//There are no guarantees about the order in which properties will be set.
#define REGISTER_PROPERTY(TYPE, TAG, SETTER_FUNC) static ComponentRegistry::RegisterProperty PROP_##SETTER_FUNC##_REGISTERED\
(COMPONENT_##TYPE##_REGISTERED,##TAG##,##SETTER_FUNC##)

namespace ComponentRegistry
{
	struct RegisterComponent
	{
		RegisterComponent(std::string name, std::function<Component * (GameObject*)> create_func);

		friend struct RegisterProperty;
	private:
		std::string tag_;
	};

	//do not try to understand how this code works, you will be sad
	using Property_Setter_Func = std::function<void(Component*, std::istringstream&)>;
	struct RegisterProperty
	{
		RegisterProperty(RegisterComponent& component, std::string property_name, Property_Setter_Func set_func);
	};

	Component* MakeComponent(std::string name, GameObject* parent);
	Property_Setter_Func SetProperty(std::string component_name, std::string prop_tag);
}
