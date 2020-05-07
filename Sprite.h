#pragma once

#include "SDL/include/SDL_surface.h"
#include "SDL_extensions/image/include/SDL_image.h"
#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Vector.h"

class Sprite : public Component
{
public:
	Sprite(GameObject* parent);

	void render() const;
	void update(float dt) {};

private:

	SDL_Texture* source_;
	Vector2 offset_;
};