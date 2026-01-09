#include "SeekBarSettings.hpp"

#include <format>

#include <SDL3/SDL.h>

#include <core/SkCanvas.h>

#include "Button.hpp"
#include "Label.hpp"
#include "SlideButton.hpp"
#include "Slider.hpp"
#include "colors/UIColors.hpp"


namespace ssb::core
{
	SeekBarSettings::SeekBarSettings(unsigned int width, unsigned int height, int x, int y, SettingsCallback settingsCallback)
		: UIItem(width, height, x, y)
		, m_settingsCallback(settingsCallback)
	{
		const auto elementCount = 7;
		const auto marginSpaceRatio = 0.15f;
		const auto marginSpace = height * marginSpaceRatio;
		const auto margin = marginSpace / (elementCount + 1);
		const auto availableSpace = height - marginSpace;

		const auto labelHeight = availableSpace * 0.15f;
		const auto labelWidth = width * 0.9f;
		const auto labelX = (width - labelWidth) / 2;
		const auto labelTextSize = labelHeight / 4;

		const auto sliderHeight = availableSpace * 0.05f;
		const auto sliderWidth = width * 0.8f;
		const auto sliderX = (width - sliderWidth) / 2;

		const auto slideButtonHeight = availableSpace * 0.15f;
		const auto slideButtonWidth = slideButtonHeight * 2;
		const auto slideButtonX = (width - slideButtonWidth) / 2;

		const auto buttonHeight = availableSpace * 0.2f;
		const auto buttonWidth = buttonHeight * 3;
		const auto buttonX = (width - buttonWidth) / 2;

		auto currentY = margin;

		m_videoDurationLabel = std::make_shared<Label>(labelWidth, labelHeight, labelX, currentY + labelHeight / 4, "", labelTextSize);
		addChild(m_videoDurationLabel);

		currentY += labelHeight + margin;

		auto updateVideoDurationLabel = [this](int value)
		{
			const int minutes = value / 60;
			const int seconds = value % 60;
			std::string text = std::format("Video duration (0:30 - 10:00):   {}:{:02}", minutes, seconds);
			m_videoDurationLabel->setText(text);
		};

		m_videoDurationSlider = std::make_shared<Slider>(sliderWidth, sliderHeight, sliderX, currentY, 30, 600, updateVideoDurationLabel);
		addChild(m_videoDurationSlider);

		currentY += sliderHeight + margin;

		m_videoChapterCountLabel = std::make_shared<Label>(labelWidth, labelHeight, labelX, currentY + labelHeight / 4, "", labelTextSize);
		addChild(m_videoChapterCountLabel);

		currentY += labelHeight + margin;

		auto updateVideoChapterCountLabel = [this](int value)
		{
			std::string text = std::format("Video chapters (1 - 10):   {}", value);
			m_videoChapterCountLabel->setText(text);
		};

		m_videoChapterCountSlider = std::make_shared<Slider>(sliderWidth, sliderHeight, sliderX, currentY, 1, 10, updateVideoChapterCountLabel);
		addChild(m_videoChapterCountSlider);

		currentY += sliderHeight + margin;

		m_videoChapterDistributionLabel = std::make_shared<Label>(labelWidth, labelHeight, labelX, currentY + labelHeight / 4, "", labelTextSize);
		addChild(m_videoChapterDistributionLabel);

		currentY += labelHeight + margin;

		auto updateVideoChapterDistributionLabel = [this](bool value)
		{
			std::string text = std::format("Random chapters (equal if off):   {}", value ? "On" : "Off");
			m_videoChapterDistributionLabel->setText(text);
		};

		m_videoChapterDistributionSlideButton = std::make_shared<SlideButton>(slideButtonWidth, slideButtonHeight, slideButtonX, currentY, updateVideoChapterDistributionLabel);
		addChild(m_videoChapterDistributionSlideButton);

		currentY += slideButtonHeight + margin;

		auto applySettings = [this]()
		{
			if (m_settingsCallback)
			{
				m_settingsCallback(m_videoDurationSlider->value(), m_videoChapterCountSlider->value(), m_videoChapterDistributionSlideButton->value());
			}
		};

		m_applyButton = std::make_shared<Button>(buttonWidth, buttonHeight, buttonX, currentY + buttonHeight / 4, "Apply", applySettings, buttonHeight / 3);
		addChild(m_applyButton);
	}
}
