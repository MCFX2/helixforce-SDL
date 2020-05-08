#pragma once

#include <string>
#include <vector>

#include "fileman.h"

class Component;

class GameObject
{
public:
	GameObject(std::string datafile);
	void update(float dt);
	void render() const;

	template<typename T>
	T* get_component() const
	{
		for (Component* c : components_)
		{
			T* comp = dynamic_cast<T*>(c);
			if (comp) return comp;
		}
		return NULL;
	}

	ObjectFile& get_source() { return file_; };

private:
	std::vector<Component*> components_;
	ObjectFile file_;
};