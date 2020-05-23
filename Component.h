#pragma once

#include "GameObject.h"

//creating a new component class is quite simple.
//It's quite lengthy to explain, though- look at Transform.h/.cpp
//for a straightforward example.

class Component
{
public:
	Component(GameObject* parent);
	virtual ~Component() {};
	virtual void update(float dt) = 0;
	virtual void render() {};
	//this function gets run after the object is fully constructed but
	//prior to the first update, equivalent to Start() in Unity.
	virtual void start() {};

	//convenience function
	template<typename T>
	T* get_component() const {
		return parent_->get_component<T>();
	}

	GameObject* get_parent() { return parent_; };

private:
	GameObject* parent_;
};