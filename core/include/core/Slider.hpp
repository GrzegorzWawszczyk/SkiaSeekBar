#pragma once

#include <functional>

#include "UIItem.hpp"
#include "Label.hpp"

class SkCanvas;

namespace ssb::core
{
	using SliderCallback = std::function<void(int)>;

	class Slider : public UIItem
	{
	public:
		Slider(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0, int minValue = 0, int maxValue = 1, SliderCallback valueChangeCallback = {});

		bool hitTest(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) const override;
		void onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;
		void onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;
		void onInputPointerMove(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;

		int value() const;
		void setValue(int value);

		void drawItem(SkCanvas* canvas) override;

	private:
		void setValueImpl(int value, bool force = false);
		float position() const;
		float thumbRadius() const;
		unsigned int thumbCenterX() const;
		unsigned int thumbCenterY() const;

		int m_minValue;
		int m_maxValue;
		int m_value;
		SliderCallback m_valueChangeCallback;
	};
}