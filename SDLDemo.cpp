// SDLDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Engine.h"

int main(int argc, char* args[])
{
    Engine::Init();

    while (true)
    {
        Engine::Update();
    }

    Engine::Shutdown();

    return 0;
}
