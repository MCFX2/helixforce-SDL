#pragma once

#include <string>
#include <vector>

#include "fileman.h"

class Level;
class Component;

class GameObject
{
public:
	GameObject(std::string datafile, Level* level);
	~GameObject();
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

	void destroy() { to_destroy_ = true; };

	Level* get_level() { return level_; };

private:
	std::vector<Component*> components_;
	Level* level_;
	ObjectFile file_;
	bool to_destroy_;
};