#include "Button.hpp"

#include <SDL3/SDL.h>

#include <include/core/SkCanvas.h>
#include <include/core/SkFont.h>
#include <include/core/SkRRect.h>

namespace ssb::core
{
    Button::Button(unsigned int width, unsigned int height, int x, int y, std::string text, Callback clickCallback)
        : UIItem(width, height, x, y)
        , m_label(std::make_shared<Label>(width, height, 0, 0, text))
        , m_pressed(false)
        , m_color(SK_ColorLTGRAY)
        , m_pressedColor(SK_ColorGRAY)
        , m_clickCallback(clickCallback)
    {
        addChild(m_label);
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
        m_pressed = true;
    }

    void Button::onInputPointerUp(const InputPointerEvent& inputPointerEvent, bool stillIn)
    {
        if (m_pressed && stillIn)
        {
            clicked();
        }
        m_pressed = false;
    }

    void Button::clicked()
    {
        SDL_Log("CLICK");
        m_clickCallback();
    }

    void Button::drawItem(SkCanvas* canvas)
    {
        SkRect rect = SkRect::MakeXYWH(0, 0, m_width, m_height);
        float radius = 1.5f;

        float strokeWidth = 1.0f;

        SkRect inner = rect.makeInset(strokeWidth / 2, strokeWidth / 2);

        SkRRect rrect;
        rrect.setRectXY(inner, radius, radius);

        SkPaint paint;

        paint.setAntiAlias(true);
        paint.setStyle(SkPaint::kFill_Style);
        paint.setColor(m_pressed ? m_pressedColor : m_color);
        canvas->drawRRect(rrect, paint);

        paint.setStyle(SkPaint::kStroke_Style);
        paint.setStrokeWidth(strokeWidth);
        paint.setColor(SK_ColorBLACK);
        canvas->drawRRect(rrect, paint);
    }
}
