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
	~Sprite();
	void render() override;
	void update(float dt) override {};
	void start() override;

	void set_source(std::string filename);

	//renders all sprites
	static void RenderAll();

	Vector2 offset{ Vector2(0) };
	unsigned layer{ 0 };
private:
	Transform* transform{ nullptr };
	SDL_Texture* source_{ nullptr };
	SDL_Rect renderable_{ 0 };
};