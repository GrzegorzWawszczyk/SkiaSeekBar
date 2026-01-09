#pragma once

#include <functional>

#include "UIItem.hpp"
#include "Label.hpp"

class SkCanvas;

namespace ssb::core
{
	using SeekBarPositionCallback = std::function<void(int)>;
	using SeekBarInputCallback = std::function<void(bool)>;

	class SeekBar : public UIItem
	{
	public:
		SeekBar(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0, unsigned int maxMsecs = 0,
			unsigned int chapterCount = 1, bool randomChapterDistribution = false);

		bool hitTest(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) const override;
		void onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;
		void onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;
		void onInputPointerMove(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;

		void setCurrentMsecs(unsigned int msecs);
		void setMaxMsecs(unsigned int msecs);
		void setChaptersInfo(unsigned int count, bool randomDistribution);

		void addCurrentMsecsChangedCallback(SeekBarPositionCallback callback);
		void addOnInputCallback(SeekBarInputCallback callback);

		void drawItem(SkCanvas* canvas) override;

	private:
		void drawBar(SkCanvas* canvas);
		void drawIndefinite(SkCanvas* canvas);
		void setCurrentMsecsPrivate(unsigned int msecs);
		float position() const;
		float thumbRadius() const;
		unsigned int thumbCenterX() const;
		unsigned int thumbCenterY() const;

		unsigned int m_currentMsecs;
		unsigned int m_maxMsecs;
		SeekBarPositionCallback m_currentMsecsChangeCallback;
		SeekBarInputCallback m_inputCallback;
		std::vector<unsigned int> m_chapters;
		bool m_activePlayback;
		float m_indeterminateOffset;
	};
}