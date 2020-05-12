
#include "SDL_extensions/image/include/SDL_image.h"
#include "Sprite.h"
#include "Engine.h"
#include <unordered_map>

#include "Vector.h"

#include "ComponentRegistry.h"
#include "screen.h"
#include "Transform.h"

#include <map>

static std::unordered_map<std::string, SDL_Texture*> Sprite_Dict;

static std::multimap<int, Sprite*> Sprite_Rendermap;

static const std::string Sprite_path = "./assets/";

static const unsigned assumedScreenX = 1280, assumedScreenY = 720;

static void SpriteSourceProperty(Component* component, std::istringstream& src)
{
	std::string filename;
	src >> filename;
	Sprite* sprite = static_cast<Sprite*>(component);
	sprite->set_source(filename);
}

REGISTER_COMPONENT("Sprite", Sprite);
REGISTER_SIMPLE_PROPERTY(Sprite, "Offset", offset);
REGISTER_SIMPLE_PROPERTY(Sprite, "Layer", layer);
REGISTER_PROPERTY(Sprite, "Spritename", SpriteSourceProperty);

void Sprite::set_source(std::string filename)
{
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

void Sprite::start()
{
	transform = get_component<Transform>();
	Sprite_Rendermap.emplace(layer, this);
}

Sprite::Sprite(GameObject* parent) : Component(parent)
{
}

Sprite::~Sprite()
{
	//search for our specific sprite
	for (auto it = Sprite_Rendermap.find(layer); it != Sprite_Rendermap.end(); ++it)
	{
		if (it->second == this)
		{
			Sprite_Rendermap.erase(it);
			break;
		}
	}
}

void Sprite::render()
{
	float wRatio = (float)Screen::Get_Screen().w / (float)assumedScreenX;
	float hRatio = (float)Screen::Get_Screen().h / (float)assumedScreenY;
	renderable_.x = (int)((offset.x + transform->translation.x) * wRatio);
	renderable_.y = (int)((offset.y + transform->translation.y) * hRatio);
	renderable_.w = (int)(transform->scale.x * wRatio);
	renderable_.h = (int)(transform->scale.y * hRatio);
	//adjust so sprite is centered
	renderable_.x -= (int)(renderable_.w * 0.5f);
	renderable_.y -= (int)(renderable_.h * 0.5f);
}

void Sprite::RenderAll()
{
	for (std::pair<int, Sprite*> renderTarget : Sprite_Rendermap)
	{
		SDL_RenderCopy(Engine::Get_Renderer(), renderTarget.second->source_, NULL,
			&renderTarget.second->renderable_);
	}
}