#pragma once

#include "GameObject.h"

//creating a new component class is quite simple.
//It's quite lengthy to explain, though- look at Transform.h/.cpp
//for a straightforward example.

class Component
{
public:
	Component(GameObject* parent);

	virtual void update(float dt) = 0;
	virtual void render() const {};

	//convenience function
	template<typename T>
	T* get_component() const
	{
		return parent_->get_component<T>();
	}

private:
	//components should not be interfacing with the parent
	//directly except during construction (to get the source file/properties).
	GameObject* parent_;
};