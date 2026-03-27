#include "Segment.h"

// Конструктор
Segment::Segment(
    const int id,
    const int start,
    const int end,
    const CRGB activeColor,
    IButton* button,
    const CRGB defaultColor
) :
    m_id(id),
    m_start(start),
    m_end(end),
    m_activeColor(activeColor),
    m_defaultColor(defaultColor),
    m_button(button),
    m_isActive(false)
{
}

// Получить текущий цвет
CRGB Segment::getCurrentColor() const
{
    return m_isActive ? m_activeColor : m_defaultColor;
}

// Отрисовать сегмент
void Segment::draw(CRGB* leds) const
{
    const CRGB color = getCurrentColor();
    for (int i = m_start; i < m_end; i++)
    {
        leds[i] = color;
    }
}

bool Segment::isButtonPressed() const
{
    return m_button && m_button->isPressed();
}