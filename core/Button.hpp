#pragma once

#include "UIItem.hpp"

#include <include/core/SkColor.h>

class SkCanvas;

namespace ssb::core
{
	class Button : public UIItem
	{
	public:
		Button(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0, bool visible = true, float opacity = 1.0f);

		bool hitTest(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) const override;
		bool reservingInput() const override;
		void onInputPointerDown(const InputPointerEvent& inputPointerEvent) override;
		void onInputPointerUp(const InputPointerEvent& inputPointerEvent, bool stillIn) override;
		//void onInputPointerMove(const InputPointerEvent& inputPointerEvent, bool stillIn) override;

		void clicked();

		void drawItem(SkCanvas* canvas) override;

	private:
		bool m_pressed;
		SkColor m_color;
		SkColor m_pressedColor;
	};
}