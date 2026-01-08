#pragma once

#include <vector>
#include <memory>

#include <SDL3/SDL.h>

#include "include/core/SkRefCnt.h"

#include "Drawable.hpp"

class SkCanvas;
class SkSurface;

namespace ssb::core
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(Renderer&&) = delete;

        void draw();
        void presentToSDL();
        void setDrawable(std::shared_ptr<Drawable> drawable);

        int getWindowWidth() const;
        int getWindowHeight() const;

    private:
        int m_windowWidth;
        int m_windowHeight;
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_sdlRenderer = nullptr;
        SDL_Texture* m_texture = nullptr;
        sk_sp<SkSurface> m_surface;
        std::shared_ptr<Drawable> m_drawable;
    };
}