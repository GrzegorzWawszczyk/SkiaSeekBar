#include "Label.hpp"

#include <cassert>

#include <SDL3/SDL.h>

#include "include/core/SkCanvas.h"

#include "include/core/SkData.h"
#include "include/core/SkFont.h"
#include "include/core/SkFontMetrics.h"
#include "include/ports/SkFontMgr_data.h"
#include "include/core/SkFontScanner.h"
#include "include/core/SkPaint.h"
#include "include/core/SkTypeface.h"

#include "fonts/Roboto-Regular.hpp"

namespace
{
    sk_sp<SkTypeface> s_typeface;

    void LoadUIFont()
    {
        sk_sp<SkData> fontData = SkData::MakeWithoutCopy(Roboto_Regular_ttf, Roboto_Regular_ttf_len);
        sk_sp<SkData> fonts[] = { fontData };
        SkSpan<sk_sp<SkData>> span(fonts, 1);
        sk_sp<SkFontMgr> fontMgr = SkFontMgr_New_Custom_Data(span);
        s_typeface = fontMgr->legacyMakeTypeface(nullptr, SkFontStyle());
    }
}

namespace ssb::core {
    Label::Label(unsigned int width, unsigned int height, int x, int y, std::string text, float fontSize, SkColor color)
        : UIItem(width, height, x, y)
        , m_text(text)
        , m_color(color)
    {
        if (!s_typeface) {
            LoadUIFont();
            assert(s_typeface && "Failed to load UI font!");
        }

        m_font = SkFont(s_typeface, 16.0f);
        m_font.setEdging(SkFont::Edging::kSubpixelAntiAlias);

        m_paint.setAntiAlias(true);
        m_paint.setColor(m_color);
    }

    void Label::setText(const std::string& text)
    {
        m_text = text;
        updateLayout();
    }

    void Label::setColor(SkColor color)
    {
        m_color = color;
        m_paint.setColor(color);
    }

    void Label::setFontSize(float size)
    {
        m_font.setSize(size);
        updateLayout();
    }

    void Label::updateLayout()
    {
        m_font.measureText(m_text.c_str(), m_text.size(), SkTextEncoding::kUTF8, &m_textBounds);
    }

    void Label::drawItem(SkCanvas* canvas)
    {
        if (!visible() || m_text.empty())
           return;

        SkRect rect = SkRect::MakeXYWH(
           (float)m_x,
           (float)m_y,
           (float)m_width,
           (float)m_height
        );

        SkFontMetrics metrics;
        m_font.getMetrics(&metrics);

        float textWidth = m_font.measureText(m_text.c_str(), m_text.size(), SkTextEncoding::kUTF8);
        float textHeight = metrics.fDescent - metrics.fAscent;

        float textX = rect.centerX() - textWidth / 2;
        float textY = rect.centerY() - (metrics.fAscent + metrics.fDescent) / 2;


        m_paint.setAlphaf(m_opacity);
        canvas->drawString(m_text.c_str(), textX, textY, m_font, m_paint);
    }

}

