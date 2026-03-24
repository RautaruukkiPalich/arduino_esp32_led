#include "Segment.h"

// Конструктор
Segment::Segment(
    const int id,
    const int start,
    const int end,
    const CRGB activeColor,
    const int buttonPin,
    const CRGB defaultColor
) :
    m_id(id),
    m_start(start),
    m_end(end),
    m_activeColor(activeColor),
    m_defaultColor(defaultColor),
    m_buttonPin(buttonPin),
    m_isActive(false),
    m_lastDebounce(0)
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

// Проверить нажатие кнопки
bool Segment::isButtonPressed()
{
    if (digitalRead(m_buttonPin) != HIGH) { return false; }

    const unsigned long now = millis();
    if (now - m_lastDebounce < DEBOUNCE_DELAY) { return false; }

    m_lastDebounce = now;
    return true;
}
