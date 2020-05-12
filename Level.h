#pragma once
#include "Component.h"
class Level : public Component
{
public:
	Level(GameObject*);
	~Level();
	void start() override;

	void update(float dt) override;
	void render() const override;


	std::string name;

	//add an object (by filename) to the level
	//it will be constructed on start()
	void add_object(std::string);

private:
	std::vector<std::string> construct_list;
	std::vector<GameObject*> object_list;
};

