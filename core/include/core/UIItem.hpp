#pragma once

#include <vector>
#include <memory>

#include "Drawable.hpp"
#include "Interactive.hpp"

namespace ssb::core
{
	class UIItem : public Drawable, public Interactive, public std::enable_shared_from_this<UIItem>
	{
	public:
		UIItem(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0, bool visible = true, float opacity = 1.0f);

		void draw(SkCanvas* canvas) final;

		void addChild(std::shared_ptr<UIItem> child);

		InputEventResult tryConsumeInput(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;

	protected:
		virtual void drawItem(SkCanvas* canvas) {}

		std::vector<std::shared_ptr<UIItem>> children;
	};
}