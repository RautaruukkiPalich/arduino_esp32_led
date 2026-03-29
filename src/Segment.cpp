#include "Segment.h"

// Конструктор
Segment::Segment(
    const int id,
    const int start,
    const int end,
    const CRGB activeColor,
    const CRGB inactiveColor,
    const CRGB defaultColor,
    const Mode mode
) :
    m_id(id),
    m_start(start),
    m_end(end),
    m_activeColor(activeColor),
    m_inactiveColor(inactiveColor),
    m_defaultColor(defaultColor),
    m_mode(mode)
{
}

// Получить текущий цвет
CRGB Segment::getCurrentColor() const
{
    switch (m_mode)
    {
        case ACTIVE_MODE: return m_activeColor;
        case INACTIVE_MODE: return m_inactiveColor;
        default: return m_defaultColor;
    }
}
