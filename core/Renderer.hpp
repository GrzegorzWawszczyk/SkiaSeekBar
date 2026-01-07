#pragma once

#include <SDL3/SDL.h>
#include <include/core/SkSurface.h>
#include <include/core/SkCanvas.h>
#ifdef __ANDROID__
#include <include/gpu/ganesh/GrDirectContext.h>
#endif

namespace ssb::core
{
    class Renderer
    {
    public:
        //#ifdef __ANDROID__
            //Renderer(); // Android: u¿ywa SDLActivity GL context
        //#else
        Renderer(); // Windows
        //#endif


            //Renderer(); // Android: u¿ywa SDLActivity GL context

        ~Renderer();

        //void attachSDL(SDL_Renderer* r);
        void draw();
        void presentToSDL();

    private:
        SDL_Window* m_window = nullptr;
        sk_sp<SkSurface> m_surface;
        SDL_Renderer* m_sdlRenderer = nullptr;
        SDL_Texture* m_texture = nullptr;
    };
}