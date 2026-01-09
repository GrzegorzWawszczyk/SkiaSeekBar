
#include "renderer.hpp"

#include <SDL3/SDL.h>

#include <core/SkCanvas.h>
#include <core/SkColor.h>
#include <core/SkImageInfo.h>
#include <core/SkPixmap.h>
#include <core/SkSurface.h>


namespace ssb::core
{
    Renderer::Renderer()
    {
        m_window = SDL_CreateWindow(
            "SkiaSeekBar",
#ifdef __ANDROID__
            0, 0,
            0
#else
            576, 1133,
            SDL_WINDOW_ALWAYS_ON_TOP
#endif
        );

        SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);

        SkImageInfo info = SkImageInfo::Make(m_windowWidth, m_windowHeight, kRGBA_8888_SkColorType, kPremul_SkAlphaType);
        m_surface = SkSurfaces::Raster(info);

        m_sdlRenderer = SDL_CreateRenderer(m_window, nullptr);
        m_texture = SDL_CreateTexture(
            m_sdlRenderer,
            SDL_PIXELFORMAT_RGBA32,
            SDL_TEXTUREACCESS_STREAMING,
            m_windowWidth,
            m_windowHeight
        );
    }

    Renderer::~Renderer()
    {
        if (m_texture) SDL_DestroyTexture(m_texture);
        if (m_sdlRenderer) SDL_DestroyRenderer(m_sdlRenderer);
        if (m_window) SDL_DestroyWindow(m_window);
    }

    void Renderer::draw()
    {
        if (!m_surface) return;

        SkCanvas* canvas = m_surface->getCanvas();

        m_drawable->draw(canvas);
    }

    void Renderer::presentToSDL()
    {
        if (!m_surface || !m_texture) return;

        SkPixmap pixmap;
        if (!m_surface->peekPixels(&pixmap)) return;

        SDL_UpdateTexture(m_texture, nullptr, pixmap.addr(0, 0), pixmap.rowBytes());
        SDL_RenderClear(m_sdlRenderer);
        SDL_RenderTexture(m_sdlRenderer, m_texture, nullptr, nullptr);
        SDL_RenderPresent(m_sdlRenderer);
    }

    void Renderer::setDrawable(std::shared_ptr<Drawable> drawable)
    {
        m_drawable = drawable;
    }

    int Renderer::getWindowWidth() const
    {
        return m_windowWidth;
    }

    int Renderer::getWindowHeight() const
    {
        return m_windowHeight;
    }
}