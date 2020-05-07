
#pragma warning(disable : 26812)
#include "SDL/include/SDL.h"

#include "SDL_extensions/image/include/SDL_image.h"

#include "Sprite.h"

#include <vector>

#include "mouse.h"
#include "keyboard.h"

enum class curScreen
{
	title,
};

static curScreen curState = curScreen::title;

static SDL_Renderer* renderer;

static std::vector<SDL_Event*> events;

namespace Engine
{
	std::vector<SDL_Event> Get_Events(unsigned min, unsigned max)
	{
		std::vector<SDL_Event> event_list;
		SDL_Event cur;
		while (SDL_PeepEvents(&cur, 1, SDL_GETEVENT, min, max))
		{
			event_list.push_back(cur);
		}
		return event_list;
	}



	void Init()
	{
		SDL_InitSubSystem(SDL_INIT_EVERYTHING);
		SDL_Window* win = SDL_CreateWindow("Bullet Chaos V9", 100, 100, 1280, 720, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

		IMG_Init(IMG_INIT_PNG);
		//SDL_Load
	}

	void Update()
	{
		SDL_PumpEvents();
		Mouse::Update();
		Keyboard::Update();
		static GameObject ply("player.dat");

		if (curState == curScreen::title)
		{
			ply.update(0);
		}

		//render handling
		SDL_RenderClear(renderer);
		if (curState == curScreen::title)
		{
			ply.render();
		}

		SDL_RenderPresent(renderer);

		//clear event stack
		SDL_Event garbage;
		while (SDL_PollEvent(&garbage)) {}
		SDL_Delay(1);
	}

	void Shutdown()
	{
		SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	}

	SDL_Renderer* Get_Renderer()
	{
		return renderer;
	}
}