#pragma once

#include "Vector.h"

struct SDL_Window;

struct Screen_Info
{
	int x, y, w, h;
	unsigned refreshRate;
	bool fullscreen;
};

namespace Screen
{ //inits the window and returns a pointer to it
	SDL_Window* Init(Screen_Info);

	Screen_Info Get_Screen();
}