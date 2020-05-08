
#include "SDL_extensions/image/include/SDL_image.h"
#include "Sprite.h"
#include "Engine.h"
#include <unordered_map>

#include "Vector.h"

#include "ComponentRegistry.h"

#include "Transform.h"

static std::unordered_map<std::string, SDL_Texture*> Sprite_Dict;

static const std::string Sprite_path = "./assets/";

//static ComponentRegistry::RegisterComponent register_sprite("Sprite", []
//	(GameObject* parent){return new Sprite(parent); });

REGISTER_COMPONENT("Sprite", Sprite);

Sprite::Sprite(GameObject* parent) : Component(parent)
{
	std::string filename;
	parent->get_source().read_properties("Sprite", filename, offset_);
	//sprites are stored in a dictionary so we don't have duplicate sprites
	auto nSprite = Sprite_Dict.find(filename);
	//sprite is not in dictionary
	if (nSprite == Sprite_Dict.end())
	{
		SDL_Texture* newSprite = IMG_LoadTexture(Engine::Get_Renderer(), (Sprite_path + filename).c_str());
		Sprite_Dict.emplace(filename, newSprite);
		source_ = newSprite;
	}
	else
	{
		source_ = nSprite->second;
	}
}

void Sprite::render() const
{
	SDL_Rect renderable;
	const Transform* transform = get_component<Transform>();

	renderable.x = (int)(offset_.x + transform->translation.x);
	renderable.y = (int)(offset_.y + transform->translation.y);
	renderable.w = (int)transform->scale.x;
	renderable.h = (int)transform->scale.y;
	//adjust so sprite is centered
	renderable.x -= (int)(renderable.w * 0.5f);
	renderable.y -= (int)(renderable.h * 0.5f);
	SDL_RenderCopy(Engine::Get_Renderer(), source_, NULL, &renderable);
}
