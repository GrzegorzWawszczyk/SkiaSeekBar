#pragma once

#include <vector>
#include <memory>

class SkCanvas;

namespace ssb::core
{
    class Drawable {
    public:
        Drawable(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0, bool visible = true, float opacity = 1.0f);

        virtual ~Drawable() = default;

        virtual void draw(SkCanvas* canvas) {}

        int x();
        void setX(int x);

        int y();
        void setY(int y);

        unsigned int width();
        void setWidth(unsigned int width);

        unsigned int height();
        void setHeight(unsigned int height);

        bool visible();
        void setVisible(bool visible);

        float opacity();
        void setOpacity(float opacity);

    protected:
        unsigned int m_width;
        unsigned int m_height;
        int m_x;
        int m_y;
        bool m_visible;
        float m_opacity;
    };

}