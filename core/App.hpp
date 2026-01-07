#pragma once

#include "renderer.hpp"

namespace ssb::core
{
	class App {
	public:
		App() = default;
		~App();

		bool Init();
		void StartLoop();

	private:
		std::unique_ptr<Renderer> m_renderer;
	};
}