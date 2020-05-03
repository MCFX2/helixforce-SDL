#pragma once

#include "SDL/include/SDL_surface.h"
#include "SDL_extensions/image/include/SDL_image.h"
#include <string>

class Sprite
{
public:
	Sprite(std::string filename);

	void Render() const;

	//temporary
	void setPos(int x, int y);
	int getX();
	int getY();

private:

	SDL_Texture* source_;
	SDL_Rect rect_;
};