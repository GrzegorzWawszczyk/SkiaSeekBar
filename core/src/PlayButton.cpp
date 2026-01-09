#include "PlayButton.hpp"

#include <core/SkCanvas.h>
#include <core/SkPath.h>

#include "colors/UIColors.hpp"

namespace
{
    constexpr SkColor kActiveColor = UIColors::Accent;
    constexpr SkColor kInactiveColor = UIColors::Off;
}

namespace ssb::core
{
	PlayButton::PlayButton(unsigned int width, unsigned int height, int x, int y)
		: UIItem(width, height, x, y)
		, m_playing(false)
        , m_active(true)
		, m_clickCallback(nullptr)

	{
	}

    void PlayButton::setPlaying(bool value)
	{
		m_playing = value;
	}

    void PlayButton::setActive(bool value)
    {
        m_active = value;
    }

    void PlayButton::addClickCallback(ButtonCallback clickCallback)
    {
        m_clickCallback = clickCallback;
    }

    bool PlayButton::hitTest(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset) const
    {
        if (!m_active)
        {
            return false;
        }

        const auto globalX = m_x + xOffset;
        const auto globalY = m_y + yOffset;
        return inputPointerEvent.x >= globalX && inputPointerEvent.x <= globalX + m_width
            && inputPointerEvent.y >= globalY && inputPointerEvent.y <= globalY + m_height;
    }

    void PlayButton::onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
        saveInputId(inputPointerEvent.id);
    }

    void PlayButton::onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
        const auto pressed = reservingInput();
        if (m_clickCallback && pressed && hitTest(inputPointerEvent, xOffset, yOffset))
        {
            m_clickCallback();
        }
        clearSavedInputId();
    }

    void PlayButton::drawItem(SkCanvas* canvas)
    {
        const auto pressed = reservingInput();

        SkPaint paint;
        paint.setAntiAlias(true);

        float cx = width() * 0.5f;
        float cy = height() * 0.5f;
        float size = std::min(width(), height()) * 0.4f;

        if (pressed)
        {
            size *= 0.9f;
        }

        paint.setColor(m_active ? kActiveColor : kInactiveColor);

        if (!m_playing)
        {
            SkPath path;
            path.moveTo(cx - size * 0.5f, cy - size);
            path.lineTo(cx - size * 0.5f, cy + size);
            path.lineTo(cx + size, cy);
            path.close();

            canvas->drawPath(path, paint);
        }
        else
        {
            float barW = size * 0.4f;
            float gap = barW * 0.5f;

            SkRect left = SkRect::MakeXYWH(cx - gap - barW, cy - size, barW, size * 2);
            SkRect right = SkRect::MakeXYWH(cx + gap, cy - size, barW, size * 2);

            canvas->drawRect(left, paint);
            canvas->drawRect(right, paint);
        }
    }

}