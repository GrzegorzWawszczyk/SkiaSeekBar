#pragma once

#include "UIItem.hpp"

class SkCanvas;

namespace ssb::core
{
	class Button;
	class Label;
	class Rect;
	class SeekBar;
	class SlideButton;
	class Slider;

	class SeekBarPanel : public UIItem
	{
	public:
		SeekBarPanel(unsigned int width, unsigned int height, int x, int y);

		void setSeekBarSetting(unsigned int duration, unsigned int chapterCount, bool randomChaptersDistribution);

		//void drawItem(SkCanvas* canvas) override;

	private:
		std::shared_ptr<Rect> m_background;
		std::shared_ptr<SeekBar> m_seekBar;
		//std::shared_ptr<Label> m_videoChapterCountLabel;
		//std::shared_ptr<Label> m_videoChapterDistributionLabel;
		//std::shared_ptr<Slider> m_videoDurationSlider;
		//std::shared_ptr<Slider> m_videoChapterCountSlider;
		//std::shared_ptr<SlideButton> m_videoChapterDistributionSlideButton;
		//std::shared_ptr<Button> m_applyButton;
	};
}