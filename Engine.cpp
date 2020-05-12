
#pragma warning(disable : 26812)
#include "SDL/include/SDL.h"

#include "SDL_extensions/image/include/SDL_image.h"

#include "Sprite.h"

#include <vector>

#include "mouse.h"
#include "keyboard.h"

#include "Utils.h"

#include <Windows.h>

#include "screen.h"

enum class curScreen
{
	title,
};

static curScreen curState = curScreen::title;

static SDL_Renderer* renderer;

static std::vector<SDL_Event*> events;

static double targetFPS = 60;

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

	GameObject* object_manager;

	void Init()
	{
		SDL_InitSubSystem(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
		object_manager = new GameObject("game.dat");
		targetFPS = Screen::Get_Screen().refreshRate;
	}

	void Update()
	{
		static double dt = 0;
		static Util::Timer frameTime;
		SDL_PumpEvents();
		Mouse::Update();
		Keyboard::Update();
		object_manager->update((float)dt);
		//render handling
		SDL_RenderClear(renderer);
		object_manager->render();
		SDL_RenderPresent(renderer);

		//clear event stack
		SDL_Event garbage;
		while (SDL_PollEvent(&garbage)) {}

		dt = frameTime.elapsed();
		if (dt < 1.f / targetFPS)
		{ //we beat the target frame time, wait out the remainder
			SDL_Delay((int)(1000 * ((1.f / targetFPS) - dt)));
			//std::this_thread::sleep_for(std::chrono::seconds((1.f / targetFPS) - dt)));
			dt = 1.f / targetFPS;
		}
		frameTime.reset();
	}

	void Shutdown()
	{
		SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	}

	void Set_Renderer(SDL_Renderer* render)
	{
		if (renderer)
		{
			SDL_DestroyRenderer(renderer);
		}
		renderer = render;
	}

	SDL_Renderer* Get_Renderer()
	{
		return renderer;
	}
}