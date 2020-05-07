#pragma once

#include "Sprite.h"
#include <string>
#include <vector>
#include "Component.h"

#include "fileman.h"


class GameObject
{
public:
	GameObject(std::string datafile);
	void update(float dt);
	void render() const;

	template<typename T>
	T* get_component()
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
	void read_(std::string filename);
};