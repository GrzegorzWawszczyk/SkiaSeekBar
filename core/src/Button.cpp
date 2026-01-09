#include "Button.hpp"

#include <core/SkCanvas.h>
#include <core/SkFont.h>
#include <core/SkRRect.h>

#include "colors/UIColors.hpp"

namespace
{
    constexpr SkColor kBaseColor = UIColors::On;
    constexpr SkColor kPressedColor = UIColors::Active;
    constexpr SkColor kTextColor = UIColors::Accent;
}

namespace ssb::core
{
    Button::Button(unsigned int width, unsigned int height, int x, int y, std::string text, ButtonCallback clickCallback, float textFontSize)
        : UIItem(width, height, x, y)
        , m_label(std::make_shared<Label>(width, height, 0, 0, text, textFontSize, kTextColor))
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

    void Button::onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
        saveInputId(inputPointerEvent.id);
    }

    void Button::onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
        const auto pressed = reservingInput();
        if (m_clickCallback && pressed && hitTest(inputPointerEvent, xOffset, yOffset))
        {
            m_clickCallback();
        }
        clearSavedInputId();
    }

    void Button::drawItem(SkCanvas* canvas)
    {
        const auto rect = SkRect::MakeXYWH(0, 0, m_width, m_height);
        const auto radius = 5.0f;

        const auto strokeWidth = 1.0f;

        const auto inner = rect.makeInset(strokeWidth / 2, strokeWidth / 2);

        SkRRect rrect;
        rrect.setRectXY(inner, radius, radius);

        SkPaint paint;

        const auto pressed = reservingInput();
        paint.setAntiAlias(true);
        paint.setStyle(SkPaint::kFill_Style);
        paint.setColor(pressed ? kPressedColor : kBaseColor);
        canvas->drawRRect(rrect, paint);

        paint.setStyle(SkPaint::kStroke_Style);
        paint.setStrokeWidth(strokeWidth);
        paint.setColor(SK_ColorBLACK);
        canvas->drawRRect(rrect, paint);
    }
}
