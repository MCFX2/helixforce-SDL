#pragma once
#include "Component.h"
class Level : public Component
{
public:
	Level(GameObject*);
	~Level();
	void start() override;

	void update(float dt) override;
	void render() override;

	//attach object to level render/destruction queue
	void attach_object(GameObject*);
	void detach_object(GameObject*);

	std::string name;

	//add an object (by filename) to the level
	//it will be constructed on start()
	void add_object(std::string);

private:
	std::vector<std::string> construct_list;
	std::vector<GameObject*> object_list;
	std::vector<GameObject*> to_remove;
	std::vector<GameObject*> to_add;
};

