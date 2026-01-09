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
        bool reservingInput() const { return m_savedInputId.has_value(); }
        void saveInputId(int inputId) { m_savedInputId = inputId; }
        bool checkIncomingInputId(int inputId) const { return m_savedInputId && m_savedInputId.value() == inputId; }
        void clearSavedInputId() { m_savedInputId = std::nullopt; }
        virtual void onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) {}
        virtual void onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) {}
        virtual void onInputPointerMove(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) {}
        virtual InputEventResult tryConsumeInput(const InputPointerEvent& inputPointerEvent, int xOffset = 0, int yOffset = 0) { return { false, std::nullopt }; }

    private:
        std::optional<int> m_savedInputId = std::nullopt;
    };
}