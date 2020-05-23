#pragma once

#include "SDL/include/SDL_scancode.h"

namespace Keyboard
{
	void Update();
	bool Get_KeyPressed(unsigned key);
	bool Get_KeyTriggered(unsigned key);
}