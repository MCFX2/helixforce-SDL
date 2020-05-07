#pragma once

class GameObject;

class Component
{
public:
	Component(GameObject* parent);

	virtual void update(float dt) = 0;
	virtual void render() {};
protected:
	GameObject* get_parent();
private:
	GameObject* parent_;
};