#include "Level.h"

#include "ComponentRegistry.h"
#include "LevelManager.h"


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

void Level::render() const
{
	for (GameObject* g : object_list)
	{
		g->render();
	}
}

void Level::update(float dt)
{
	for (GameObject* g : object_list)
	{
		g->update(dt);
	}
}

void Level::start()
{
	for (std::string s : construct_list)
	{
		object_list.push_back(new GameObject(s));
	}
}