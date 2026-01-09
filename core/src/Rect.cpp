#include "Rect.hpp"

#include <core/SkCanvas.h>

namespace ssb::core
{
    Rect::Rect(unsigned int width, unsigned int height, int x, int y, SkColor color, bool visible, float opacity)
        : UIItem(width, height, x, y, visible, opacity)
        , m_color(color)
    {
    }

    void Rect::drawItem(SkCanvas* canvas)
    {
        SkPaint paint;
        paint.setColor(m_color);
        canvas->drawRect(SkRect::MakeXYWH(0, 0, m_width, m_height), paint); // x, y = 0, as already translated in Drawable::drawAll()
    }
}
