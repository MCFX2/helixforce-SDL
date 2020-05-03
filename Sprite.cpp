
#include "SDL_extensions/image/include/SDL_image.h"
#include "Sprite.h"
#include "Engine.h"
#include <map>

static std::map<std::string, SDL_Texture*> Sprite_Dict;

Sprite::Sprite(std::string filename)
{
	//Sprite_Dict.
	auto nSprite = Sprite_Dict.find(filename);
	//sprite is not in dictionary
	if (nSprite == Sprite_Dict.end())
	{
		SDL_Texture* newSprite = IMG_LoadTexture(Engine::Get_Renderer(), filename.c_str());
		Sprite_Dict.emplace(filename, newSprite);
		source_ = newSprite;
	}
	else
	{
		source_ = nSprite->second;
	}

	rect_.x = 10;
	rect_.y = 10;
	rect_.w = 100;
	rect_.h = 100;
}

void Sprite::Render() const
{
	SDL_Rect renderable = rect_;
	renderable.x -= renderable.w * 0.5f;
	renderable.y -= renderable.h * 0.5f;
	SDL_RenderCopy(Engine::Get_Renderer(), source_, NULL, &renderable);
}

void Sprite::setPos(int x, int y)
{
	rect_.x = x;
	rect_.y = y;
}

int Sprite::getX()
{
	return rect_.x;
}

int Sprite::getY()
{
	return rect_.y;
}