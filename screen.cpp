#include "screen.h"

#include <Windows.h>

#include "SDL/include/SDL.h"

//static float maxScreenX, maxScreenY;

#include "Engine.h"

Screen_Info scrInfo;

static const int Window_Flags = SDL_WINDOW_SHOWN;
static const int Fullscreen_Flags = SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS;

static SDL_Window* nWin;

namespace Screen
{
	SDL_Window* Init(Screen_Info scr)
	{
		SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
		scrInfo = scr;
		if (nWin)
		{ //destroy previous window
			SDL_DestroyWindow(nWin);
		}
		nWin = SDL_CreateWindow("Helix Force SDL", scrInfo.x, scrInfo.y, scrInfo.w, scrInfo.h, SDL_WINDOW_SHOWN);
		return nWin;
	}
	Screen_Info Get_Screen()
	{
		return scrInfo;
	}
}