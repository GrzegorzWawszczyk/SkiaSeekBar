#include <iostream>

#include <SDL3/SDL.h>

#include <GLES3/gl3.h>

#include "App.hpp"

extern "C" int SDL_main(int, char**)
{
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles2");
    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
    
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