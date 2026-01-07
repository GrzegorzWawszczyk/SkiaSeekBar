#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <iostream>
#include "app.hpp"

int main(int, char**) {
    ssb::core::App app;
    if (!app.Init())
    {
        std::cerr << "App init failed" << std::endl;
        return 1;
    }
    app.StartLoop();

    return 0;
}
