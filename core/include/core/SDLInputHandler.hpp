#pragma once

#include <vector>
#include <memory>

#include <SDL3/SDL_events.h>

#include "Interactive.hpp"

namespace ssb::core
{
	class SDLInputHandler {
	public:
		SDLInputHandler(int windowWidth, int windowHeight);
		~SDLInputHandler() = default;
		SDLInputHandler(const SDLInputHandler&) = delete;
		SDLInputHandler& operator=(const SDLInputHandler&) = delete;
		SDLInputHandler(SDLInputHandler&&) = delete;
		SDLInputHandler& operator=(SDLInputHandler&&) = delete;

		void setInteractive(std::shared_ptr<Interactive> interactive);

		void handleSDLEvent(const SDL_Event& event);

	private:
		std::shared_ptr<Interactive> m_defaultInteractive;
		std::vector<ReservedInput> m_reservedInputs;
		unsigned int m_windowWidth;
		unsigned int m_windowHeight;
	};
}