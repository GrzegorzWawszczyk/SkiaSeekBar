#pragma once

#include <functional>

#include "UIItem.hpp"

class SkCanvas;

namespace ssb::core
{
	using SettingsCallback = std::function<void(unsigned int, unsigned int, bool)>;

	class Button;
	class Label;
	class SlideButton;
	class Slider;

	class SeekBarSettings : public UIItem
	{
	public:
		SeekBarSettings(unsigned int width, unsigned int height, int x, int y, SettingsCallback settingsCallback = nullptr);

	private:
		std::shared_ptr<Label> m_videoDurationLabel;
		std::shared_ptr<Label> m_videoChapterCountLabel;
		std::shared_ptr<Label> m_videoChapterDistributionLabel;
		std::shared_ptr<Slider> m_videoDurationSlider;
		std::shared_ptr<Slider> m_videoChapterCountSlider;
		std::shared_ptr<SlideButton> m_videoChapterDistributionSlideButton;
		std::shared_ptr<Button> m_applyButton;

		SettingsCallback m_settingsCallback;
	};
}