#include "UIItem.hpp"

#include <ranges>

#include <include/core/SkCanvas.h>

namespace ssb::core
{
	UIItem::UIItem(unsigned int width, unsigned int height, int x, int y, bool visible, float opacity)
		: Drawable(width, height, x, y, visible, opacity)
	{
	}

	void UIItem::draw(SkCanvas* canvas)
	{
		if (!m_visible) return;

		canvas->save();
		canvas->translate(m_x, m_y);

		drawItem(canvas);
		for (auto& child : children) {
			child->draw(canvas);
		}

		canvas->restore();

	}

	void UIItem::addChild(std::shared_ptr<UIItem> child)
	{
		children.push_back(child);
	}

	InputEventResult UIItem::tryConsumeInput(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
		for (auto& child : children | std::views::reverse)
		{
			const auto inputEventResult = child->tryConsumeInput(inputPointerEvent, xOffset + m_x, yOffset + m_y);
			if (inputEventResult.consumed)
			{
				return inputEventResult;
			}
		}

		const auto isHit = hitTest(inputPointerEvent, xOffset, yOffset);
        if (reservingInput() || isHit) {
            switch (inputPointerEvent.type)
			{
				case InputPointerEvent::Type::Down:
					onInputPointerDown(inputPointerEvent);
					break;
				case InputPointerEvent::Type::Up:
					onInputPointerUp(inputPointerEvent, isHit);
					break;
				case InputPointerEvent::Type::Move:
					onInputPointerMove(inputPointerEvent, isHit);
					break;
				case InputPointerEvent::Type::Cancel:
					break;
            }
			std::shared_ptr<Interactive> thisReservingInput = reservingInput() ? shared_from_this() : nullptr;
			return { true, thisReservingInput ? std::make_optional<ReservedInput>(thisReservingInput, xOffset, yOffset, inputPointerEvent.id) : std::nullopt };
        }

		return { false, std::nullopt };
    }
}
