#pragma once

#include <core/SkColor.h>

#include "UIItem.hpp"

class SkCanvas;

namespace ssb::core
{
	class Rect : public UIItem
	{
	public:
		Rect(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0, SkColor color = SK_ColorWHITE, bool visible = true, float opacity = 1.0f);
		void drawItem(SkCanvas* canvas) override;

	private:
		SkColor m_color;
	};
}