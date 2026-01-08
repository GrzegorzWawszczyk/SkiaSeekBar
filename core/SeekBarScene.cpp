#include "SeekBarScene.hpp"

#include <SDL3/SDL.h>

#include "Button.hpp"
#include "Label.hpp"
#include "Rect.hpp"

#include <include/core/SkCanvas.h>

namespace ssb::core
{
	SeekBarScene::SeekBarScene()
	{
		auto rect = std::make_shared<Rect>(200, 200, 250);
		addChild(rect);

		auto button = std::make_shared<Button>(200, 100, 50, 50, "GUZICZEK!", []() {
				SDL_Log("ANO CLICK");
			});
		rect->addChild(button);

		auto button2 = std::make_shared<Button>(200, 100, 50, 300, "GUZICZEK2!", []() {
			SDL_Log("ANO CLICK2");
			});
		rect->addChild(button2);
	}

	void SeekBarScene::drawItem(SkCanvas* canvas)
	{
        canvas->clear(SK_ColorDKGRAY);
	}
}
