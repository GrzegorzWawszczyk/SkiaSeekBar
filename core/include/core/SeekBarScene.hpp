#pragma once

#include "UIItem.hpp"

class SkCanvas;

namespace ssb::core
{
	class SeekBarPanel;
	class SeekBarSettings;

	class SeekBarScene : public UIItem
	{
	public:
		SeekBarScene(unsigned int width, unsigned int height);

		void drawItem(SkCanvas* canvas) override;

	private:
		std::shared_ptr<SeekBarPanel> m_seekBarPanel;
		std::shared_ptr<SeekBarSettings> m_seekBarSettings;
	};
}