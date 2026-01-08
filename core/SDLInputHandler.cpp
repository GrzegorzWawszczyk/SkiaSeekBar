#include "SDLInputHandler.hpp"

#include <SDL3/SDL.h>


namespace ssb::core
{
	SDLInputHandler::SDLInputHandler(int windowWidth, int windowHeight)
		: m_defaultInteractive(nullptr)
		, m_reservedInput(std::nullopt)
		, m_windowWidth(windowWidth)
		, m_windowHeight(windowHeight)
	{		
	}

	void SDLInputHandler::setInteractive(std::shared_ptr<Interactive> interactive)
	{
		m_defaultInteractive = interactive;
	}

	void SDLInputHandler::handleSDLEvent(const SDL_Event& event)
	{
		InputPointerEvent inputPointerEvent;
		switch (event.type) {
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			inputPointerEvent.type = InputPointerEvent::Type::Down;
			inputPointerEvent.x = event.button.x;
			inputPointerEvent.y = event.button.y;
			inputPointerEvent.id = 0;
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			inputPointerEvent.type = InputPointerEvent::Type::Up;
			inputPointerEvent.x = event.button.x;
			inputPointerEvent.y = event.button.y;
			inputPointerEvent.id = 0;
			break;
		case SDL_EVENT_MOUSE_MOTION:
			inputPointerEvent.type = InputPointerEvent::Type::Move;
			inputPointerEvent.x = event.motion.x;
			inputPointerEvent.y = event.motion.y;
			inputPointerEvent.id = 0;
			break;
		case SDL_EVENT_FINGER_DOWN:
			inputPointerEvent.type = InputPointerEvent::Type::Down;
			inputPointerEvent.x = event.tfinger.x * m_windowWidth;
			inputPointerEvent.y = event.tfinger.y * m_windowHeight;
			inputPointerEvent.id = event.tfinger.fingerID;
			break;
		case SDL_EVENT_FINGER_UP:
			inputPointerEvent.type = InputPointerEvent::Type::Up;
			inputPointerEvent.x = event.tfinger.x * m_windowWidth;
			inputPointerEvent.y = event.tfinger.y * m_windowHeight;
			inputPointerEvent.id = event.tfinger.fingerID;
			break;
		case SDL_EVENT_FINGER_MOTION:
			inputPointerEvent.type = InputPointerEvent::Type::Move;
			inputPointerEvent.x = event.tfinger.x * m_windowWidth;
			inputPointerEvent.y = event.tfinger.y * m_windowHeight;
			inputPointerEvent.id = event.tfinger.fingerID;
			break;
		case SDL_EVENT_FINGER_CANCELED:
			inputPointerEvent.type = InputPointerEvent::Type::Cancel;
			inputPointerEvent.x = event.tfinger.x * m_windowWidth;
			inputPointerEvent.y = event.tfinger.y * m_windowHeight;
			inputPointerEvent.id = event.tfinger.fingerID;
			break;
		default:
			return;
		}

		InputEventResult inputEventResult;
		const auto reservedInput = m_reservedInput.value_or({});

		if (reservedInput.inputReservingInteractive)
		{
			inputEventResult = reservedInput.inputReservingInteractive->tryConsumeInput(inputPointerEvent, reservedInput.xOffset, reservedInput.yOffset);
		}
		else
		{
			inputEventResult = m_defaultInteractive->tryConsumeInput(inputPointerEvent);
		}

		if (inputEventResult.consumed && inputEventResult.reservedInput)
		{
			m_reservedInput = inputEventResult.reservedInput;
		}
		else
		{
			m_reservedInput = std::nullopt;
		}
	}
}
