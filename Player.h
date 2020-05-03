#pragma once

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();

	void update(float dt) override;

private:

};