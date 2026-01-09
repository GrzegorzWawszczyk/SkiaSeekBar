#include "UIItem.hpp"

#include <ranges>

#include <core/SkCanvas.h>

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
		if (inputPointerEvent.type == InputPointerEvent::Type::Down)
		{
			int a = 5;
		}
		for (auto& child : children | std::views::reverse)
		{
			const auto inputEventResult = child->tryConsumeInput(inputPointerEvent, xOffset + m_x, yOffset + m_y);
			if (inputEventResult.consumed)
			{
				return inputEventResult;
			}
		}

        if (checkIncomingInputId(inputPointerEvent.id) || hitTest(inputPointerEvent, xOffset, yOffset)) {
            switch (inputPointerEvent.type)
			{
				case InputPointerEvent::Type::Down:
					onInputPointerDown(inputPointerEvent, xOffset, yOffset);
					break;
				case InputPointerEvent::Type::Up:
					onInputPointerUp(inputPointerEvent, xOffset, yOffset);
					break;
				case InputPointerEvent::Type::Move:
					onInputPointerMove(inputPointerEvent, xOffset, yOffset);
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
