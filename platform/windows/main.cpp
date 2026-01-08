#define SDL_MAIN_HANDLED

#include <iostream>

#include <SDL3/SDL.h>

#include "App.hpp"

int main(int, char**) {
    ssb::core::App app;
    if (!app.Init())
    {
        std::cerr << "App init failed" << std::endl;
        return 1;
    }

    app.InitScene();
    app.StartLoop();

    return 0;
}
