#pragma once

#include <functional>

#include <core/SkColor.h>

#include "UIItem.hpp"
#include "Label.hpp"

class SkCanvas;

namespace ssb::core
{
	using ButtonCallback = std::function<void()>;

	class Button : public UIItem
	{
	public:
		Button(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0, std::string text = "", ButtonCallback clickCallback = nullptr, float textFontSize = 16.0f);

		bool hitTest(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) const override;
		void onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;
		void onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;

		void drawItem(SkCanvas* canvas) override;

	private:
		std::shared_ptr<Label> m_label = nullptr;
		ButtonCallback m_clickCallback;
	};
}