#include "keyboard.h"

#include "Engine.h"

#include "SDL/include/SDL_keyboard.h"

#include <array>

struct keyState
{
	bool isDown;
	bool wasDown; //true if key was down last tick
};

static std::array<keyState, SDL_NUM_SCANCODES> keyStates;

void Keyboard::Update()
{
	auto keyboard_events = Engine::Get_Events(SDL_KEYDOWN, SDL_KEYUP);

	for (keyState k : keyStates)
	{
		k.wasDown = k.isDown;
	}

	for (SDL_Event e : keyboard_events)
	{
		keyStates[e.key.keysym.scancode].isDown = e.type == SDL_KEYDOWN;
	}
}

bool Keyboard::Get_KeyPressed(unsigned key)
{
	return keyStates[key].isDown;
}

bool Keyboard::Get_KeyTriggered(unsigned key)
{
	return keyStates[key].isDown && !keyStates[key].wasDown;
}