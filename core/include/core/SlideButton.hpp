#pragma once

#include <functional>

#include "UIItem.hpp"

namespace ssb::core
{
	using SlideButtonCallback = std::function<void(bool)>;

	class SlideButton : public UIItem
	{
	public:
		SlideButton(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0, SlideButtonCallback callback = nullptr, bool initialValue = false);

		bool hitTest(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) const override;
		void onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;
		void onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;

		void drawItem(SkCanvas* canvas) override;

		bool value() const;
		void setValue(bool value);

	private:
		void setValueImpl(bool value, bool force = false);

		bool m_value;
		SlideButtonCallback m_valueChangeCallback;
	};
}
