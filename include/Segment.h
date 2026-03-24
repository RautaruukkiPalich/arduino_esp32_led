#pragma once

#include <Arduino.h>
#include <FastLED.h>


// ========== КЛАСС СЕГМЕНТА ==========
class Segment
{
    const int m_id; // Номер сегмента
    const int m_start; // Начальный LED
    const int m_end; // Конечный LED
    const CRGB m_activeColor; // Цвет в активном состоянии
    const CRGB m_defaultColor; // Цвет в неактивном состоянии
    const int m_buttonPin; // Пин кнопки
    bool m_isActive; // Активен ли сегмент
    unsigned long m_lastDebounce; // Для антидребезга
    static constexpr unsigned long DEBOUNCE_DELAY = 200;

public:
    // Конструктор
    Segment(
        int id,
        int start,
        int end,
        CRGB activeColor,
        int buttonPin,
        CRGB defaultColor = CRGB::Black
    );

    // Геттеры
    int getId() const { return m_id; }
    int getStart() const { return m_start; }
    int getEnd() const { return m_end; }
    int getLength() const { return m_end - m_start; }
    CRGB getActiveColor() const { return m_activeColor; }
    CRGB getDefaultColor() const { return m_defaultColor; }
    int getButtonPin() const { return m_buttonPin; }
    bool isActive() const { return m_isActive; }

    // Управление состоянием
    void activate() { m_isActive = true; }
    void deactivate() { m_isActive = false; }
    void toggle() { m_isActive = !m_isActive; }

    // Получить текущий цвет (активный или дефолтный)
    CRGB getCurrentColor() const;
    // Отрисовать сегмент на ленте
    void draw(CRGB* leds) const;
    // Проверить, нажата ли кнопка этого сегмента (с антидребезгом)
    bool isButtonPressed();
};
