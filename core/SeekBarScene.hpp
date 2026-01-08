#pragma once

#include "UIItem.hpp"

class SkCanvas;

namespace ssb::core
{
	class SeekBarScene : public UIItem
	{
	public:
		SeekBarScene();

		void drawItem(SkCanvas* canvas) override;

	private:
	};
}