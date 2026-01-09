#pragma once

#include <functional>

#include "UIItem.hpp"

namespace ssb::core
{
    using ButtonCallback = std::function<void()>;

    class PlayButton : public UIItem
    {
    public:
        PlayButton(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0);

        void setPlaying(bool value);
        void setActive(bool value);
        void addClickCallback(ButtonCallback clickCallback);

        bool hitTest(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) const override;
        void onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;
        void onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) override;

        void drawItem(SkCanvas* canvas) override;

    private:
        bool m_playing;
        bool m_active;
        ButtonCallback m_clickCallback;
    };

}