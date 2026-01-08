#include "SeekBarScene.hpp"

#include "Button.hpp"
#include "Rect.hpp"

#include <include/core/SkCanvas.h>

namespace ssb::core
{
	SeekBarScene::SeekBarScene()
	{
		auto rect = std::make_shared<Rect>(200, 200, 250);
		addChild(rect);
		//addChild(std::move(rect));
		auto rect2 = std::make_shared<Rect>(200, 200, 0, 100, SK_ColorLTGRAY);
		rect->addChild(rect2);
		//auto rect3 = std::make_shared<Rect>(200, 200, 50, 50, SK_ColorGRAY);
		//rect->addDrawableChild(rect3);
		//auto rect4 = std::make_shared<Rect>(100, 100, 100, 100, SK_ColorRED);
		//rect3->addDrawableChild(rect4);
		auto button = std::make_shared<Button>(200, 100, 50, 50);
		rect2->addChild(button);
		//auto button2 = std::make_shared<Button>(50, 50, 25, 25, SK_ColorRED);
		//rect2->addChild(button2);
		//addDrawableChild(button);
		//addInteractiveChild(button);
	}

	void SeekBarScene::drawItem(SkCanvas* canvas)
	{
        canvas->clear(SK_ColorDKGRAY);
	}
}
