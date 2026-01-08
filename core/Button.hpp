#pragma once

#include <functional>

#include <include/core/SkColor.h>

#include "UIItem.hpp"
#include "Label.hpp"

class SkCanvas;

namespace ssb::core
{
	using Callback = std::function<void()>;

	class Button : public UIItem
	{
	public:
		Button(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0, std::string text = "", Callback clickCallback = {});

		bool hitTest(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) const override;
		bool reservingInput() const override;
		void onInputPointerDown(const InputPointerEvent& inputPointerEvent) override;
		void onInputPointerUp(const InputPointerEvent& inputPointerEvent, bool stillIn) override;

		void clicked();

		void drawItem(SkCanvas* canvas) override;

	private:
		std::shared_ptr<Label> m_label = nullptr;
		bool m_pressed;
		SkColor m_color;
		SkColor m_pressedColor;
		Callback m_clickCallback;
	};
}