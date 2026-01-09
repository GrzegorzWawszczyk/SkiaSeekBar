#include "SlideButton.hpp"

#include <core/SkCanvas.h>
#include <core/SkRRect.h>

#include "colors/UIColors.hpp"

namespace
{
	constexpr SkColor kOffColor = UIColors::Off;
	constexpr SkColor kOnColor = UIColors::Active;
	constexpr SkColor kThumbColor = UIColors::Accent;
}

namespace ssb::core
{
	SlideButton::SlideButton(unsigned int width, unsigned int height, int x, int y, SlideButtonCallback callback, bool initialValue)
		: UIItem(width, height, x, y)
		, m_valueChangeCallback(callback)
	{
		setValueImpl(initialValue, true);
	}

	bool SlideButton::hitTest(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset) const
	{
		const auto globalX = m_x + xOffset;
		const auto globalY = m_y + yOffset;

		const auto radius = m_height / 2.0f;

		if (inputPointerEvent.x >= globalX + radius && inputPointerEvent.x <= globalX + m_width - radius &&
			inputPointerEvent.y >= globalY && inputPointerEvent.y <= globalY + m_height)
			return true;

		auto deltaX = inputPointerEvent.x - (globalX + radius);
		auto deltaY = inputPointerEvent.y - (globalY + radius);
		if (deltaX * deltaX + deltaY * deltaY <= radius * radius)
			return true;

		deltaX = inputPointerEvent.x - (globalX + m_width - radius);
		deltaY = inputPointerEvent.y - (globalY + radius);
		if (deltaX * deltaX + deltaY * deltaY <= radius * radius)
			return true;

		return false;
	}

	void SlideButton::onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
	{
		saveInputId(inputPointerEvent.id);
	}

	void SlideButton::onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
	{
		const auto pressed = reservingInput();
		if (pressed && hitTest(inputPointerEvent, xOffset, yOffset))
		{
			setValue(!m_value);
		}
		clearSavedInputId();
	}

	void SlideButton::drawItem(SkCanvas* canvas)
	{
		SkPaint paint;
		paint.setAntiAlias(true);

		const auto rect = SkRect::MakeXYWH(0, 0, m_width, m_height);
		float radius = m_height / 2.0f;

		SkRRect bgRect;
		bgRect.setRectXY(rect, radius, radius);
		paint.setColor(m_value ? kOnColor : kOffColor);
		canvas->drawRRect(bgRect, paint);

		paint.setColor(kThumbColor);
		float thumbRadius = 0.9f * (m_height / 2.0f);
		float thumbCenterX = m_value ? m_width - m_height / 2 : m_height / 2;
		float thumbCenterY = m_height / 2.0f;
		canvas->drawCircle(thumbCenterX, thumbCenterY, thumbRadius, paint);
	}

	bool SlideButton::value() const
	{
		return m_value;
	}

	void SlideButton::setValue(bool value)
	{
		setValueImpl(value);
	}

	void SlideButton::setValueImpl(bool value, bool force)
	{
		if (value != m_value || force)
		{
			m_value = value;
			if (m_valueChangeCallback)
			{
				m_valueChangeCallback(m_value);
			}
		}
	}
}
