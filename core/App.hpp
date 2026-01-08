#pragma once

#include <memory>

#include "Renderer.hpp"
#include "SDLInputHandler.hpp"

namespace ssb::core
{
	class SeekBarScene;

	class App {
	public:
		App() = default;
		~App();
		App(const App&) = delete;
		App& operator=(const App&) = delete;
		App(App&&) = delete;
		App& operator=(App&&) = delete;

		bool Init();
		void StartLoop();

	private:
		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<SDLInputHandler> m_inputHandler;
		std::shared_ptr<SeekBarScene> m_seekBarScene;
	};
}