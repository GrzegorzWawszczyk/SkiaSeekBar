#pragma once

#include "PlayState.hpp"
#include "UIItem.hpp"

class SkCanvas;

namespace ssb::core
{
	class InputArea;
	class Label;
	class PlayButton;
	class Rect;
	class SeekBar;

	class SeekBarPanel : public UIItem
	{
	public:
		SeekBarPanel(unsigned int width, unsigned int height, int x, int y);

		void setSeekBarSetting(unsigned int duration, unsigned int chapterCount, bool randomChaptersDistribution);

		void drawItem(SkCanvas* canvas) override;

	private:
		PlayState m_playState;
		std::shared_ptr<Rect> m_background;
		std::shared_ptr<SeekBar> m_seekBar;
		std::shared_ptr<PlayButton> m_playButton;
		std::shared_ptr<Label> m_playbackTimeLabel;
		std::shared_ptr<InputArea> m_leftInputArea;
		std::shared_ptr<InputArea> m_rightInputArea;
	};
}