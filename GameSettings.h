#pragma once
#include "Component.h"
#include "Vector.h"

class GameSettings : public Component
{
public:
	GameSettings(GameObject* parent);
	void update(float dt) override {};
	void start() override;

	Vector2 resolution{ Vector2(1280, 720) };
	Vector2 window_position{ Vector2(50, 50) };
	unsigned refresh_rate{ 60 };
	bool fullscreen{ 0 };
	std::string starting_level{ "" };
};

