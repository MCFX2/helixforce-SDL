#pragma once

#include "Vector.h"

namespace Mouse
{
	void Update();

	//returns the x, y position of the mouse
	Vector2 Get_Pos();
	//return the x, y position of the mouse last frame
	Vector2 Get_LastPos();

	//returns true if the button is being held (see SDL_Event.h for IDs)
	bool Get_ButtonDown(unsigned);
	//returns true for the first frame the button was held
	bool Get_ButtonTriggered(unsigned);
	//returns true for the first frame the button was released
	bool Get_ButtonReleased(unsigned);

}