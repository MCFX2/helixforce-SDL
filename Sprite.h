#pragma once

#include "SDL/include/SDL_surface.h"
#include "SDL_extensions/image/include/SDL_image.h"
#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Vector.h"

class Transform;

class Sprite : public Component
{
public:
	Sprite(GameObject* parent);

	void render() const override;
	void update(float dt) override {};
	void start() override;

	void set_source(std::string filename);

	Vector2 offset{ Vector2(0) };
private:
	Transform* transform;
	SDL_Texture* source_{ nullptr };
};