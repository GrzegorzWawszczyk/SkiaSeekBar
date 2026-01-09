#pragma once

#include <functional>

#include "UIItem.hpp"

class SkCanvas;

namespace ssb::core
{
	using InputAreaCallback = std::function<void()>;

	class InputArea : public UIItem
	{
	public:
		InputArea(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0);

		bool hitTest(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) const override;
		void onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;
		void onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;

		void addClickCallback(InputAreaCallback callback);
		void addDoubleClickCallback(InputAreaCallback callback);

		void drawItem(SkCanvas* canvas) override;

	private:
		uint64_t m_lastClickTime = 0;
		bool m_waitingForClick = false;
		InputAreaCallback m_clickCallback;
		InputAreaCallback m_doubleClickCallback;
	};
}