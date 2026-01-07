
#include "renderer.hpp"

#include <include/core/SkImageInfo.h>
#include <include/core/SkColor.h>
#include <include/core/SkPixmap.h>
#include <SDL3/SDL.h>

namespace {
    int xPos = 0;
}

namespace ssb::core
{
    Renderer::Renderer()
    {
        m_window = SDL_CreateWindow(
            "SkiaSeekBar",
#ifdef __ANDROID__
            0, 0,
            SDL_WINDOW_FULLSCREEN
#else
            576, 1133,
            SDL_WINDOW_RESIZABLE
#endif
        );

        int width, height;
        SDL_GetWindowSize(m_window, &width, &height);

        SkImageInfo info = SkImageInfo::Make(width, height, kRGBA_8888_SkColorType, kPremul_SkAlphaType);
        m_surface = SkSurfaces::Raster(info);

        m_sdlRenderer = SDL_CreateRenderer(m_window, nullptr);
        m_texture = SDL_CreateTexture(
            m_sdlRenderer,
            SDL_PIXELFORMAT_RGBA32,
            SDL_TEXTUREACCESS_STREAMING,
            width,
            height
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
        canvas->clear(SK_ColorBLUE);

        SkPaint paint;
        paint.setColor(SK_ColorRED);
        canvas->drawRect(SkRect::MakeXYWH(xPos, 100, 200, 200), paint);
        ++xPos;
        if (xPos > 1000) xPos = 0;
    }

    void Renderer::presentToSDL()
    {
        if (!m_surface || !m_texture) return;

        SkPixmap pixmap;
        if (!m_surface->peekPixels(&pixmap)) return;

        //void* pixels = nullptr;
        //int pitch = 0;
        //if (!SDL_LockTexture(m_texture, nullptr, &pixels, &pitch)) {
        //    SDL_Log("SDL_LockTexture failed: %s", SDL_GetError());
        //    return;
        //}

        SDL_UpdateTexture(m_texture, nullptr, pixmap.addr(0, 0), pixmap.rowBytes());
        SDL_RenderClear(m_sdlRenderer);
        SDL_RenderTexture(m_sdlRenderer, m_texture, nullptr, nullptr);
        SDL_RenderPresent(m_sdlRenderer);


        //for (int y = 0; y < pixmap.height(); y++) {
        //    memcpy(static_cast<uint8_t*>(pixels) + y * pitch,
        //        pixmap.addr(0, y),
        //        pixmap.width() * 4);
        //}

        //SDL_UnlockTexture(m_texture);
        //SDL_RenderClear(m_sdlRenderer);
        //SDL_RenderTexture(m_sdlRenderer, m_texture, nullptr, nullptr);
        //SDL_RenderPresent(m_sdlRenderer);
    }
}