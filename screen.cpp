#include "screen.h"

#include <Windows.h>

#include "SDL/include/SDL.h"

//static float maxScreenX, maxScreenY;

Screen_Info scrInfo;

namespace Screen
{
	SDL_Window* Init()
	{
		SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
		//maxScreenX = GetSystemMetrics(SM_CXSCREEN);
		//maxScreenY = GetSystemMetrics(SM_CYSCREEN);

		scrInfo.refreshRate = 60;
		scrInfo.x = 50;
		scrInfo.y = 50;
		scrInfo.w = 1280;
		scrInfo.h = 720;

		return SDL_CreateWindow("Helix Force SDL", scrInfo.x, scrInfo.y, scrInfo.w, scrInfo.h, SDL_WINDOW_SHOWN);
	}
}