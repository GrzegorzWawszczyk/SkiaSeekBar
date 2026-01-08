#pragma once

#include "UIItem.hpp"
#include "include/core/SkFont.h"
#include "include/core/SkPaint.h"
#include "include/core/SkTypeface.h"
#include "include/core/SkFontMgr.h"
#include <string>

namespace ssb::core {

    class Label : public UIItem {
    public:
        Label(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0, std::string text = "", float fontSize = 16.0f, SkColor color = SK_ColorBLACK);

        void setText(const std::string& text);
        void setColor(SkColor color);
        void setFontSize(float size);

    protected:
        void drawItem(SkCanvas* canvas) override;

    private:
        void updateLayout();

    private:
        std::string m_text;
        SkColor m_color;

        SkFont m_font;
        SkPaint m_paint;

        SkRect m_textBounds;
        bool m_dirty = true;
    };

}
