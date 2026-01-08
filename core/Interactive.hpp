#pragma once

#include <memory>
#include <optional>

namespace ssb::core
{
    class Interactive;

    struct InputPointerEvent
    {
        enum class Type { Down, Up, Move, Cancel };
        Type type;
        int x = 0;
        int y = 0;
        int id = 0;
    };

    struct ReservedInput
    {
        std::shared_ptr<Interactive> inputReservingInteractive = nullptr;
        int xOffset = 0;
        int yOffset = 0;
        int id = 0;
    };

    struct InputEventResult
    {
        bool consumed = false;
        std::optional<ReservedInput> reservedInput = std::nullopt;
    };

    class Interactive
    {
    public:
        virtual bool hitTest(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) const { return false; }
        virtual bool reservingInput() const { return false; }
        virtual void onInputPointerDown(const InputPointerEvent& inputPointerEvent) {}
        virtual void onInputPointerUp(const InputPointerEvent& inputPointerEvent, bool stillIn) {}
        virtual void onInputPointerMove(const InputPointerEvent& inputPointerEvent, bool stillIn) {}
        virtual InputEventResult tryConsumeInput(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) { return { false, std::nullopt }; }
    };
}