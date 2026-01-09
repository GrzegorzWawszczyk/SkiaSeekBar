#include "SeekBarPanel.hpp"

#include <format>

#include <core/SkCanvas.h>

#include "InputArea.hpp"
#include "Label.hpp"
#include "PlayButton.hpp"
#include "Rect.hpp"
#include "SeekBar.hpp"


namespace ssb::core
{
	SeekBarPanel::SeekBarPanel(unsigned int width, unsigned int height, int x, int y)
		: UIItem(width, height, x, y)
	{
		m_background = std::make_shared<Rect>(width, height, 0, 0, SK_ColorBLACK);
		addChild(m_background);

		const auto playButtonSize = width / 15;
		const auto seekBarHeight = height * 0.03f;
		const auto inputAreaHeight = height - playButtonSize - seekBarHeight;

		m_leftInputArea = std::make_shared<InputArea>(width / 2, inputAreaHeight, 0, 0);
		addChild(m_leftInputArea);
		m_rightInputArea = std::make_shared<InputArea>(width / 2, inputAreaHeight, width / 2, 0);
		addChild(m_rightInputArea);

		auto triggerPlay = [this]()
		{
			m_playState.trigger();
		};

		auto skipBackward = [this]()
		{
			m_playState.skipBySeconds(-10);
		};
		auto skipForward = [this]()
		{
			m_playState.skipBySeconds(10);
		};


		m_leftInputArea->addClickCallback(triggerPlay);
		m_rightInputArea->addClickCallback(triggerPlay);
		m_leftInputArea->addDoubleClickCallback(skipBackward);
		m_rightInputArea->addDoubleClickCallback(skipForward);

		m_seekBar = std::make_shared<SeekBar>(width, seekBarHeight, 0, height - playButtonSize - seekBarHeight, 0);
		addChild(m_seekBar);

		m_playButton = std::make_shared<PlayButton>(playButtonSize, playButtonSize, 0, height - playButtonSize);
		addChild(m_playButton);
		m_playButton->setActive(false);

		m_playbackTimeLabel = std::make_shared<Label>(width / 5, playButtonSize, playButtonSize * 1.5f, height - playButtonSize, "", playButtonSize / 2);
		addChild(m_playbackTimeLabel);

		auto updateButton = [this](bool playing)
		{
			m_playButton->setPlaying(playing);
		};
		auto updateBar = [this](int msecs, int duration)
		{
			const auto currentFullSeconds = msecs / 1000;
			const auto currentMinutes = currentFullSeconds / 60;
			const auto currentSeconds = currentFullSeconds % 60;

			const auto durationFullSeconds = duration / 1000;
			const auto durationMinutes = durationFullSeconds / 60;
			const auto durationSeconds = durationFullSeconds % 60;

			m_seekBar->setCurrentMsecs(msecs);
			std::string text = std::format("{:02}:{:02}/{:02}:{:02}", currentMinutes, currentSeconds, durationMinutes, durationSeconds);
			m_playbackTimeLabel->setText(text);
		};
		auto deactivatePanel = [this]()
		{
			m_playState.setDuration(0);
			m_playButton->setActive(false);
			m_seekBar->setMaxMsecs(0);
			m_playbackTimeLabel->setText("");
		};
		m_playState.addPlaybackStateChangeCallback(updateButton);
		m_playState.addPlaybackFinishedCallback(deactivatePanel);
		m_playState.addPlaybackValueChangeCallback(updateBar);

		m_playButton->addClickCallback(triggerPlay);

		auto setPlaybackFreeze = [this](bool freeze)
		{
			freeze ? m_playState.freeze() : m_playState.unfreeze();
		};
		m_seekBar->addOnInputCallback(setPlaybackFreeze);

		auto updatePlayState = [this](unsigned int msecs)
		{
			m_playState.setPlaybackPosition(msecs);
		};
		m_seekBar->addCurrentMsecsChangedCallback(updatePlayState);
	}

	void SeekBarPanel::setSeekBarSetting(unsigned int duration, unsigned int chapterCount, bool randomChaptersDistribution)
	{
		const auto msecsDuration = duration * 1000;
		m_seekBar->setMaxMsecs(msecsDuration);
		m_seekBar->setChaptersInfo(chapterCount, randomChaptersDistribution);
		m_playButton->setActive(true);
		m_playButton->setPlaying(false);
		m_playState.setDuration(msecsDuration);
	}

	void SeekBarPanel::drawItem(SkCanvas* canvas)
	{
		// VERY, VERY HACKY, caused by the lack of time, I'm sorry
		m_playState.update();
	}
}
