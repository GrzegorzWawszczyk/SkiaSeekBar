#include "Button.hpp"

#include <SDL3/SDL.h>

#include <include/core/SkCanvas.h>
#include <include/core/SkFont.h>
#include <include/core/SkRRect.h>

namespace ssb::core
{
    ssb::core::Button::Button(unsigned int width, unsigned int height, int x, int y, bool visible, float opacity)
        : UIItem(width, height, x, y, visible, opacity)
        , m_pressed(false)
        , m_color(SK_ColorLTGRAY)
        , m_pressedColor(SK_ColorRED)
    {
    }

    bool Button::hitTest(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset) const
    {
        const auto globalX = m_x + xOffset;
        const auto globalY = m_y + yOffset;
        return inputPointerEvent.x >= globalX && inputPointerEvent.x <= globalX + m_width
            && inputPointerEvent.y >= globalY && inputPointerEvent.y <= globalY + m_height;
    }

    bool Button::reservingInput() const
    {
        return m_pressed;
    }

    void Button::onInputPointerDown(const InputPointerEvent& inputPointerEvent)
    {
        //SDL_Log("onInputPointerDown x= %i, y= %i, id= %i", inputPointerEvent.x, inputPointerEvent.y, inputPointerEvent.id);
        m_pressed = true;
    }

    void Button::onInputPointerUp(const InputPointerEvent& inputPointerEvent, bool stillIn)
    {
        //SDL_Log("onInputPointerUp x= %i, y= %i, id= %i, stillIn= %i, this= %p", inputPointerEvent.x, inputPointerEvent.y, inputPointerEvent.id, stillIn, this);
        if (m_pressed && stillIn)
        {
            clicked();
        }
        m_pressed = false;
    }

    //void Button::onInputPointerMove(const InputPointerEvent& inputPointerEvent, bool stillIn)
    //{
    //    SDL_Log("onInputPointerMove x= %i, y= %i, id= %i, stillIn= %i, this= %p", inputPointerEvent.x, inputPointerEvent.y, inputPointerEvent.id, stillIn, this);
    //    if (m_pressed)
    //    {
    //        if (stillIn)
    //        {
    //            SDL_Log("DRAGGING INSIDE");
    //        }
    //        else
    //        {
    //            SDL_Log("DRAGGING OUTSIDE");
    //        }
    //    }
    //}

    void Button::clicked()
    {
        SDL_Log("CLICK");
    }

    void Button::drawItem(SkCanvas* canvas)
    {
        SkRect rect = SkRect::MakeXYWH(0, 0, m_width, m_height);
        float radius = 1.5f;

        float strokeWidth = 1.0f;

        SkRect inner = rect.makeInset(strokeWidth / 2, strokeWidth / 2);

        SkRRect rrect;
        rrect.setRectXY(inner, radius, radius);

        SkPaint p;

        p.setAntiAlias(true);
        p.setStyle(SkPaint::kFill_Style);
        p.setColor(m_pressed ? m_pressedColor : m_color);
        canvas->drawRRect(rrect, p);

        p.setStyle(SkPaint::kStroke_Style);
        p.setStrokeWidth(strokeWidth);
        p.setColor(SK_ColorBLACK);
        canvas->drawRRect(rrect, p);



        ///text
        const char* text = "Volume";

sk_sp<SkTypeface> typeface = SkTypeface::MakeDefault();

SkFont font(typeface, 16.0f);
font.setEdging(SkFont::Edging::kSubpixelAntiAlias);


        SkPaint textPaint;
        textPaint.setAntiAlias(true);
        textPaint.setColor(SK_ColorBLACK);

        SkRect textBounds;
        font.measureText(text, strlen(text), SkTextEncoding::kUTF8, &textBounds);

        float textX = rect.centerX() - textBounds.width() / 2 - textBounds.left();
        float textY = rect.centerY() + textBounds.height() / 2 - textBounds.bottom();

        canvas->drawString(text, textX, textY, font, textPaint);

    }
}
