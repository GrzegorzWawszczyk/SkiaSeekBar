#include "App.hpp"

namespace ssb::core
{
	App::~App()
	{
		SDL_Quit();
	}
	bool App::Init()
	{
		if (!SDL_Init(SDL_INIT_VIDEO))
		{
			return false;
		}

		m_renderer = std::make_unique<Renderer>();

		return true;
	}

	void App::StartLoop()
	{
		bool running = true;
		while (running) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_EVENT_QUIT)
					running = false;
			}

			m_renderer->draw();
			m_renderer->presentToSDL();

			SDL_Delay(16); // ~60 FPS
		}
	}
}
