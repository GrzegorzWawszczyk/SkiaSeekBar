#include "InputArea.hpp"

#include <SDL3/SDL.h>

namespace
{
    static constexpr uint64_t kDoubleClickThreshold = 300;
}

namespace ssb::core
{
    InputArea::InputArea(unsigned int width, unsigned int height, int x, int y)
        : UIItem(width, height, x, y)
        , m_clickCallback(nullptr)
        , m_doubleClickCallback(nullptr)
    {
    }

    bool InputArea::hitTest(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset) const
    {
        const auto globalX = m_x + xOffset;
        const auto globalY = m_y + yOffset;
        return inputPointerEvent.x >= globalX && inputPointerEvent.x <= globalX + m_width
            && inputPointerEvent.y >= globalY && inputPointerEvent.y <= globalY + m_height;
    }

    void InputArea::onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
        saveInputId(inputPointerEvent.id);
    }

    void InputArea::onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
        const auto pressed = reservingInput();
        if (!pressed || !hitTest(inputPointerEvent, xOffset, yOffset))
        {
            clearSavedInputId();
            return;
        }

        uint64_t now = SDL_GetTicks();

        if (now - m_lastClickTime <= kDoubleClickThreshold)
        {
            if (m_doubleClickCallback)
                m_doubleClickCallback();

            m_lastClickTime = 0; 
            m_waitingForClick = false;
        }
        else
        {
            m_lastClickTime = now;
            m_waitingForClick = true;
        }

        clearSavedInputId();
    }

    void InputArea::addClickCallback(InputAreaCallback callback)
    {
        m_clickCallback = callback;
    }

    void InputArea::addDoubleClickCallback(InputAreaCallback callback)
    {
        m_doubleClickCallback = callback;
    }

    void InputArea::drawItem(SkCanvas* canvas)
    {
        if (m_waitingForClick)
        {
            uint64_t now = SDL_GetTicks();
            if (now - m_lastClickTime > kDoubleClickThreshold)
            {
                if (m_clickCallback)
                    m_clickCallback();

                m_waitingForClick = false;
            }
        }
    }

}
