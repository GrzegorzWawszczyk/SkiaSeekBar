#include "SeekBarScene.hpp"

#include <core/SkCanvas.h>

#include "SeekBarSettings.hpp"
#include "SeekBarPanel.hpp"
#include "colors/UIColors.hpp"


namespace ssb::core
{
	SeekBarScene::SeekBarScene(unsigned int width, unsigned int height)
		: UIItem(width, height)
	{
		m_seekBarPanel = std::make_shared<SeekBarPanel>(width, height * 0.4f, 0, 0);
		addChild(m_seekBarPanel);

		auto applySettings = [this](unsigned int duration, unsigned int chapters, bool randDist)
		{
			m_seekBarPanel->setSeekBarSetting(duration, chapters, randDist);
		};
		m_seekBarSettings = std::make_shared<SeekBarSettings>(width, height * 0.6f, 0, height * 0.4f, applySettings);
		addChild(m_seekBarSettings);
	}

	void SeekBarScene::drawItem(SkCanvas* canvas)
	{
        canvas->clear(UIColors::Background);
	}
}
