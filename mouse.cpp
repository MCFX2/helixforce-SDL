#include "mouse.h"
#include "Engine.h"
#include "screen.h"
#include <array>

static const unsigned int MouseEvent_Min = SDL_MOUSEMOTION;
static const unsigned int MouseEvent_Max = SDL_MOUSEWHEEL;

static Vector2 curPos;
static Vector2 lastPos;

static const Vector2 assumedScreen(1280, 720);

static const unsigned int maxHandledMouseButton = SDL_BUTTON_X2;
struct mouseButtonStateContainer
{
	std::array<bool, maxHandledMouseButton> curStates;
	std::array<bool, maxHandledMouseButton> triggeredStates;
	std::array<bool, maxHandledMouseButton> releasedStates;

} mouseButtons;

namespace Mouse
{
	void update_mouse_pos()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		curPos = Vector2((float)x, (float)y) / Vector2(
			(float)Screen::Get_Screen().w, (float)Screen::Get_Screen().h);
		curPos *= assumedScreen; //correct for other resolutions
	}

	void tick_mouse_states()
	{ 
		lastPos = curPos;
		//clear "released" and "triggered" flags
		for (bool& state : mouseButtons.releasedStates)
		{
			state = false;
		}
		for (bool& state : mouseButtons.triggeredStates)
		{
			state = false;
		}
	}

	void set_mouse_state(unsigned button, bool state)
	{
		if (!state)
		{ //button was released
			//if button was being held, set 'released' flag to true
			mouseButtons.releasedStates[button] = mouseButtons.curStates[button];
		}
		else
		{ //button was pressed
			//if button was not being held, set triggered flag
			mouseButtons.triggeredStates[button] = !mouseButtons.curStates[button];
		}
		mouseButtons.curStates[button] = state;
	}

	void Update()
	{
		tick_mouse_states();
		std::vector<SDL_Event> event_list = Engine::Get_Events(MouseEvent_Min, MouseEvent_Max);
		for (SDL_Event e : event_list)
		{
			switch (e.type)
			{
			case(SDL_MOUSEMOTION):
				update_mouse_pos();
				break;
			case(SDL_MOUSEBUTTONDOWN):
				set_mouse_state(e.button.button, true);
				break;
			case(SDL_MOUSEBUTTONUP):
				set_mouse_state(e.button.button, false);
			}
		}
	}

	Vector2 Get_Pos()
	{
		return curPos;
	}

	Vector2 Get_LastPos()
	{
		return lastPos;
	}

	bool Get_ButtonDown(unsigned i)
	{
		return mouseButtons.curStates[i];
	}

	bool Get_ButtonTriggered(unsigned i)
	{
		return mouseButtons.triggeredStates[i];
	}

	bool Get_ButtonReleased(unsigned i)
	{
		return mouseButtons.releasedStates[i];
	}
}