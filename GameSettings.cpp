#include "GameSettings.h"

#include "ComponentRegistry.h"
#include "Engine.h"
#include "screen.h"

#include "SDL/include/SDL.h"

REGISTER_COMPONENT("GameSettings", GameSettings);
REGISTER_SIMPLE_PROPERTY(GameSettings, "Resolution", resolution);
REGISTER_SIMPLE_PROPERTY(GameSettings, "WindowPosition", window_position);
REGISTER_SIMPLE_PROPERTY(GameSettings, "RefreshRate", refresh_rate);
REGISTER_SIMPLE_PROPERTY(GameSettings, "Fullscreen", fullscreen);
REGISTER_SIMPLE_PROPERTY(GameSettings, "FirstLevel", starting_level);

GameSettings::GameSettings(GameObject* parent) :Component(parent)
{

}

void GameSettings::start()
{ //init video settings
	Screen_Info s;
	s.x = (int)window_position.x;
	s.y = (int)window_position.y;
	s.w = (int)resolution.x;
	s.h = (int)resolution.y;
	s.refreshRate = refresh_rate;
	Engine::Set_Renderer(SDL_CreateRenderer(Screen::Init(s), -1, SDL_RENDERER_ACCELERATED));

	//init level

}