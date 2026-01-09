#include "Slider.hpp"

#include <core/SkCanvas.h>
#include <core/SkFont.h>
#include <core/SkRRect.h>

#include "colors/UIColors.hpp"

namespace
{
    constexpr SkColor kBaseColor = UIColors::Off;
    constexpr SkColor kFillColor = UIColors::Active;
    constexpr SkColor kThumbColor = UIColors::Accent;
}

namespace ssb::core
{
    Slider::Slider(unsigned int width, unsigned int height, int x, int y, int minValue, int maxValue, SliderCallback valueChangeCallback)
        : UIItem(width, height, x, y)
        , m_minValue(minValue)
        , m_maxValue(maxValue)
        , m_valueChangeCallback(valueChangeCallback)
    {
        setValue(minValue);
    }

    bool Slider::hitTest(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset) const
    {
        const auto globalX = m_x + xOffset;
        const auto globalY = m_y + yOffset;

        if (inputPointerEvent.x >= globalX && inputPointerEvent.x <= globalX + m_width
            && inputPointerEvent.y >= globalY && inputPointerEvent.y <= globalY + m_height)
            return true;

        const auto normalizedThumbCenterX = thumbCenterX() + xOffset + m_x;
        const auto normalizedThumbCenterY = thumbCenterY() + yOffset + m_y;

        const auto deltaX = inputPointerEvent.x - normalizedThumbCenterX;
        const auto deltaY = inputPointerEvent.y - normalizedThumbCenterY;

        return (deltaX * deltaX + deltaY * deltaY) <= (thumbRadius() * thumbRadius());
    }

    void Slider::onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
        const auto normalizedX = inputPointerEvent.x - xOffset - m_x;
        const auto normalizedY = inputPointerEvent.y - yOffset - m_y;
        const auto position = static_cast<float>(normalizedX) / m_width;
        setValue(static_cast<int>(std::round(position * (m_maxValue - m_minValue) + m_minValue)));
        saveInputId(inputPointerEvent.id);
    }

    void Slider::onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
        clearSavedInputId();
    }

    void Slider::onInputPointerMove(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
        const auto dragging = reservingInput();
        if (dragging)
        {
            onInputPointerDown(inputPointerEvent, xOffset, yOffset);
        }
    }

    void Slider::drawItem(SkCanvas* canvas)
    {
        SkPaint paint;
        paint.setAntiAlias(true);
        const auto rect = SkRect::MakeXYWH(0, 0, m_width, m_height);

        float radius = m_height / 2;
        SkRRect bgRect;
        bgRect.setRectXY(rect, radius, radius);
        paint.setColor(kBaseColor);
        canvas->drawRRect(bgRect, paint);

        SkRect fillRectBounds = rect;
        fillRectBounds.fRight = fillRectBounds.fLeft + m_width * position() + radius;
        SkRRect fillRect;
        fillRect.setRectXY(fillRectBounds, radius, radius);
        paint.setColor(kFillColor);
        canvas->drawRRect(fillRect, paint);

        paint.setColor(kThumbColor);
        canvas->drawCircle(thumbCenterX(), thumbCenterY(), thumbRadius(), paint);
    }

    int Slider::value() const
    {
        return m_value;
    }

    void Slider::setValue(int value)
    {
        setValueImpl(value);
    }

    void Slider::setValueImpl(int value, bool force)
    {
        value = std::clamp(value, m_minValue, m_maxValue);
        if (value != m_value || force )
        {
            m_value = value;
            m_valueChangeCallback(value);
        }
    }

    float Slider::position() const
    {
        return static_cast<float>(m_value - m_minValue) /
            static_cast<float>(m_maxValue - m_minValue);
    }

    float Slider::thumbRadius() const
    {
        return 0.85f * m_height ;
    }

    unsigned int Slider::thumbCenterX() const
    {
        return m_width * position();
    }

    unsigned int Slider::thumbCenterY() const
    {
        return m_height / 2.0f;
    }
}
