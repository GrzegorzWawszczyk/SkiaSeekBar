#include "SeekBar.hpp"

#include <algorithm>
#include <numeric>
#include <random>

#include <SDL3/SDL.h>

#include <core/SkCanvas.h>
#include <core/SkFont.h>
#include <core/SkRRect.h>

#include "colors/UIColors.hpp"

namespace
{
    constexpr SkColor kBaseColor = UIColors::Off;
    constexpr SkColor kFillColor = UIColors::Active;
    constexpr SkColor kThumbColor = UIColors::Accent;
}

namespace ssb::core
{
    SeekBar::SeekBar(unsigned int width, unsigned int height, int x, int y, unsigned int maxMsecs, SeekBarCallback currentMsecsChangeCallback,
        unsigned int chapterCount, bool randomChapterDistribution)
        : UIItem(width, height, x, y)
        , m_maxMsecs(maxMsecs)
        , m_currentMsecs(0)
        , m_currentMsecsChangeCallback()
    {
        setCurrentMsecs(0, true);
        setChaptersInfo(chapterCount, randomChapterDistribution);
    }

    bool SeekBar::hitTest(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset) const
    {
        if (m_maxMsecs == 0)
        {
            return false;
        }

        const auto globalX = m_x + xOffset;
        const auto globalY = m_y + yOffset;

        return inputPointerEvent.x >= globalX && inputPointerEvent.x <= globalX + m_width
            && inputPointerEvent.y >= globalY && inputPointerEvent.y <= globalY + m_height;
    }

    void SeekBar::onInputPointerDown(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
       auto normalizedX = inputPointerEvent.x - xOffset - m_x;
       auto normalizedY = inputPointerEvent.y - yOffset - m_y;
       const auto position = std::max(static_cast<float>(normalizedX) / m_width, 0.0f);
       setCurrentMsecs(static_cast<int>(std::round(position * m_maxMsecs)));
       saveInputId(inputPointerEvent.id);
    }

    void SeekBar::onInputPointerUp(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
       clearSavedInputId();
    }

    void SeekBar::onInputPointerMove(const InputPointerEvent& inputPointerEvent, int xOffset, int yOffset)
    {
       const auto dragging = reservingInput();
       if (dragging)
       {
           onInputPointerDown(inputPointerEvent, xOffset, yOffset);
       }
    }

    void SeekBar::drawItem(SkCanvas* canvas)
    {
        if (m_maxMsecs > 0)
        {
            drawBar(canvas);
        }
        else
        {
            drawIndefinite(canvas);
        }
    }

    void SeekBar::drawBar(SkCanvas* canvas)
    {
        SkPaint paint;
        paint.setAntiAlias(true);

        auto x = 0.0f;
        const auto gap = 5.0f;
        const auto total = static_cast<float>(m_maxMsecs);
        const auto fillPos = m_width * position();
        const auto currentTime = position() * total;
        const auto duringInteraction = reservingInput();

        std::vector<float> accumulated(m_chapters.size());
        std::partial_sum(m_chapters.begin(), m_chapters.end(), accumulated.begin(),
            [](unsigned int lhs, unsigned int rhs) { return static_cast<float>(lhs) + static_cast<float>(rhs); });

        auto it = std::lower_bound(accumulated.begin(), accumulated.end(), currentTime);
        size_t currentChapter = std::distance(accumulated.begin(), it);

        for (size_t i = 0; i < m_chapters.size(); ++i)
        {
            const auto segmentWidth = m_width * (static_cast<float>(m_chapters[i]) / total);
            const auto drawWidth = std::max(0.0f, segmentWidth - gap);

            const auto isCurrent = (i == currentChapter) && duringInteraction;
            const auto rectHeight = isCurrent ? m_height : m_height / 2;
            const auto rectY = isCurrent ? 0 : m_height / 4;

            if (drawWidth > 0.0f)
            {
                const auto bgRect = SkRect::MakeXYWH(x, rectY, drawWidth, rectHeight);
                paint.setColor(kBaseColor);
                canvas->drawRect(bgRect, paint);
            }

            if (x < fillPos)
            {
                const auto fillSegmentWidth = std::min(drawWidth, fillPos - x);
                if (fillSegmentWidth > 0.0f)
                {
                    const auto fillRect = SkRect::MakeXYWH(x, rectY, fillSegmentWidth, rectHeight);
                    paint.setColor(kFillColor);
                    canvas->drawRect(fillRect, paint);
                }
            }

            x += segmentWidth;
        }

        if (duringInteraction)
        {
            paint.setColor(kThumbColor);
            const auto clampedThumbX = std::clamp(static_cast<float>(thumbCenterX()), thumbRadius(), m_width - thumbRadius());
            canvas->drawCircle(clampedThumbX, thumbCenterY(), thumbRadius(), paint);
        }
    }

    void SeekBar::drawIndefinite(SkCanvas* canvas)
    {
        m_indeterminateOffset += 0.5f / 60;
        if (m_indeterminateOffset > 1.0f)
        {
            m_indeterminateOffset -= 1.0f;
        }

        const auto rectY = m_height / 4;
        const auto rectHeight = m_height / 2;

        SkPaint paint;
        paint.setAntiAlias(true);

        const auto bgRect = SkRect::MakeXYWH(0, rectY, m_width, rectHeight);
        paint.setColor(kBaseColor);
        canvas->drawRect(bgRect, paint);

        const auto segmentWidth = m_width / 2;

        const auto x = m_indeterminateOffset * m_width;

        if (x + segmentWidth <= m_width)
        {
            const auto fillRect = SkRect::MakeXYWH(x, rectY, segmentWidth, rectHeight);
            paint.setColor(kFillColor);
            canvas->drawRect(fillRect, paint);
        }
        else
        {
            const auto firstPart = m_width - x;
            const auto secondPart = segmentWidth - firstPart;

            const auto fillRect1 = SkRect::MakeXYWH(x, rectY, firstPart, rectHeight);
            const auto fillRect2 = SkRect::MakeXYWH(0, rectY, secondPart, rectHeight);

            paint.setColor(kFillColor);
            canvas->drawRect(fillRect1, paint);
            canvas->drawRect(fillRect2, paint);
        }
    }

    void SeekBar::setMaxMsecs(unsigned int msecs)
    {
        msecs = std::max(msecs, 1u);
        if (msecs != m_maxMsecs)
        {
            m_maxMsecs = msecs;
            setCurrentMsecs(0, true);
        }
    }

    void SeekBar::setChaptersInfo(unsigned int count, bool randomDistribution)
    {
        count = std::clamp(count, 1u, std::max(m_maxMsecs, 1u));
        if (count == 1)
        {
            m_chapters = std::vector<unsigned int>{ m_maxMsecs };
        }
        if (randomDistribution)
        {
            std::random_device rd;
            std::mt19937 gen(rd());

            unsigned int minSegment = m_maxMsecs / 20;
            unsigned int remaining = m_maxMsecs - minSegment * count;

            std::vector<unsigned int> segments(count);

            std::uniform_int_distribution<unsigned int> dis(0, remaining);
            std::vector<unsigned int> cuts(count - 1);
            std::generate(cuts.begin(), cuts.end(), [&]() { return dis(gen); });
            std::sort(cuts.begin(), cuts.end());

            unsigned int previous = 0;
            for (unsigned int i = 0; i < count - 1; ++i)
            {
                segments[i] = cuts[i] - previous + minSegment;
                previous = cuts[i];
            }
            segments.back() = remaining - previous + minSegment;

            m_chapters = std::move(segments);
        }
        else
        {
            m_chapters = std::vector<unsigned int>(count, m_maxMsecs / count);
            m_chapters.back() += m_maxMsecs % count;
        }
    }

    void SeekBar::setCurrentMsecs(unsigned int msecs, bool force)
    {
        msecs = std::clamp(msecs, 0u, m_maxMsecs);
        if (msecs != m_currentMsecs)
        {
            m_currentMsecs = msecs;
            if (m_currentMsecsChangeCallback)
            {
                m_currentMsecsChangeCallback(m_currentMsecs);
            }
        }
    }

    float SeekBar::position() const
    {
        return static_cast<float>(m_currentMsecs) / static_cast<float>(m_maxMsecs);
    }

    float SeekBar::thumbRadius() const
    {
        return 0.85f * m_height ;
    }

    unsigned int SeekBar::thumbCenterX() const
    {
        return m_width * position();
    }

    unsigned int SeekBar::thumbCenterY() const
    {
        return m_height / 2.0f;
    }
}
