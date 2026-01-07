#include <SDL3/SDL.h>
#include <GLES3/gl3.h>
#include <iostream>

#include "app.hpp"

extern "C" int SDL_main(int, char**)
{
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles2");

    //SDL_Window* window = SDL_CreateWindow("SkiaSeekBar", 1080, 1920, 0);
    //// SDL_Renderer* r = SDL_CreateRenderer(window, nullptr);
    //// SDL_RenderPresent(r);

    //Renderer renderer(window);
    //// renderer.attachSDL(r);

    //bool running = true;
    //SDL_Event e;

    //while (running) {
    //    while (SDL_PollEvent(&e))
    //    {
    //        switch (e.type) {
    //            case SDL_EVENT_QUIT:
    //                running = false;
    //                break;

    //            case SDL_EVENT_FINGER_DOWN:
    //                SDL_Log("Finger DOWN id=%llu x=%.3f y=%.3f pressure=%.2f",
    //                        e.tfinger.fingerID,
    //                        e.tfinger.x,
    //                        e.tfinger.y,
    //                        e.tfinger.pressure);
    //                break;

    //            case SDL_EVENT_FINGER_UP:
    //                SDL_Log("Finger UP id=%llu x=%.3f y=%.3f",
    //                        e.tfinger.fingerID,
    //                        e.tfinger.x,
    //                        e.tfinger.y);
    //                break;

    //            case SDL_EVENT_FINGER_MOTION:
    //                SDL_Log("Finger MOTION id=%llu x=%.3f y=%.3f dx=%.3f dy=%.3f",
    //                        e.tfinger.fingerID,
    //                        e.tfinger.x,
    //                        e.tfinger.y,
    //                        e.tfinger.dx,
    //                        e.tfinger.dy);
    //                break;
    //        }
    //    }

    //    renderer.draw();
    //    renderer.presentToSDL();

    //    SDL_Delay(16);
    //}

    ssb::core::App app;
    if (!app.Init())
    {
        std::cerr << "App init failed" << std::endl;
        return 1;
    }
    app.StartLoop();

    return 0;
}