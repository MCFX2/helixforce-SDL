#pragma once

#include "Sprite.h"
#include <string>
#include <vector>
#include "Component.h"



class GameObject
{
public:
	class ComponentNotFoundException : public std::exception
	{
		ComponentNotFoundException(std::string compName);
	};

	GameObject(std::string spritename) : sprite_(spritename){};
	virtual void update(float dt) = 0;
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

protected:
	Sprite sprite_;

private:
	std::vector<Component*> components_;

	void read_(std::string filename);
};