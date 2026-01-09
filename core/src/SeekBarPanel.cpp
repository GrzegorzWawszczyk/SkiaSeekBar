#include "SeekBarPanel.hpp"

#include <format>

#include <SDL3/SDL.h>

#include <core/SkCanvas.h>

#include "Button.hpp"
#include "Label.hpp"
#include "Rect.hpp"
#include "SeekBar.hpp"
#include "SlideButton.hpp"
#include "Slider.hpp"
#include "colors/UIColors.hpp"


namespace ssb::core
{
	SeekBarPanel::SeekBarPanel(unsigned int width, unsigned int height, int x, int y)
		: UIItem(width, height, x, y)
	{
		m_background = std::make_shared<Rect>(width, height, 0, 0, SK_ColorBLACK);
		addChild(m_background);

		m_seekBar = std::make_shared<SeekBar>(width, height * 0.03f, 0, height * 0.9f);
		addChild(m_seekBar);
	}

	void SeekBarPanel::setSeekBarSetting(unsigned int duration, unsigned int chapterCount, bool randomChaptersDistribution)
	{
		m_seekBar->setMaxMsecs(duration);
		m_seekBar->setChaptersInfo(chapterCount, randomChaptersDistribution);
	}
}
