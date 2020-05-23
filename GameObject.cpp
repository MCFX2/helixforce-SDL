#include "GameObject.h"

#include "Component.h"
#include "Level.h"

void GameObject::render() const
{
	for (Component* c : components_)
	{
		c->render();
	}
}

void GameObject::update(float dt)
{
	if (to_destroy_)
	{
		if (level_)level_->detach_object(this);
		else delete this;
	}
	else
	{
		for (Component* c : components_)
		{
			c->update(dt);
		}
	}
}

GameObject::~GameObject()
{
	for (Component* c : components_)
	{
		delete c;
	}
}

GameObject::GameObject(std::string datafile, Level* level) : file_(datafile),
	level_(level)
{
	if(level_) level_->attach_object(this);
	components_ = file_.construct_components(this);
	for (Component* c : components_)
	{
		c->start();
	}
}
