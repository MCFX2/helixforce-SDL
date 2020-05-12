#include "GameObject.h"

#include "Component.h"

void GameObject::render() const
{
	for (Component* c : components_)
	{
		c->render();
	}
}

void GameObject::update(float dt)
{
	for (Component* c : components_)
	{
		c->update(dt);
	}
}

GameObject::GameObject(std::string datafile) : file_(datafile)
{
	components_ = file_.construct_components(this);
	for (Component* c : components_)
	{
		c->start();
	}
}
