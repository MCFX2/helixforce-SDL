#pragma once

#include <vector>
#include "SDL/include/SDL_events.h"

typedef struct SDL_Renderer SDL_Renderer;

namespace Engine
{
	//returns a vector of all events between the given ranges (see SDL_events.h)
	//and removes them from the event stack.
	std::vector<SDL_Event> Get_Events(unsigned min, unsigned max);

	void Init();
	void Update();
	void Shutdown();

	SDL_Renderer* Get_Renderer();
	void Set_Renderer(SDL_Renderer*);
}