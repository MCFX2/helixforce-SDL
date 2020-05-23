#include "Level.h"

#include "ComponentRegistry.h"
#include "LevelManager.h"
#include "Sprite.h"

static void LevelNameProperty(Component* c, std::istringstream& ss)
{
	Level* level = static_cast<Level*>(c);
	ss >> level->name;
	LevelManager::Register_Level(level);
}

static void ObjectProperty(Component* c, std::istringstream& ss)
{
	Level* level = static_cast<Level*>(c);
	std::string obj;
	ss >> obj;
	level->add_object(obj);
}
REGISTER_COMPONENT("Level", Level);
REGISTER_PROPERTY(Level, "Name", LevelNameProperty);
REGISTER_PROPERTY(Level, "Object", ObjectProperty);

Level::Level(GameObject* parent) : Component(parent)
{

}

Level::~Level()
{
	for (GameObject* g : object_list)
	{
		delete g;
	}
}

void Level::add_object(std::string filename)
{
	construct_list.push_back(filename);
}

void Level::attach_object(GameObject* obj)
{
	to_add.push_back(obj);
}

void Level::detach_object(GameObject* obj)
{
	to_remove.push_back(obj);
}

void Level::render()
{
	for (GameObject* g : object_list)
	{
		g->render();
	}
	Sprite::RenderAll();
}

void Level::update(float dt)
{
	for (GameObject* g : object_list)
	{
		g->update(dt);
	}
	for (GameObject* ga : to_add)
	{
		object_list.push_back(ga);
	}
	to_add.clear();

	for (GameObject* gr : to_remove)
	{
		auto r = std::find(object_list.begin(), object_list.end(), gr);
		if (r != object_list.end())
		{
			object_list.erase(r);
		}
		delete gr;
	}
	to_remove.clear();

}

void Level::start()
{
	for (std::string s : construct_list)
	{
		new GameObject(s, this);
	}
}