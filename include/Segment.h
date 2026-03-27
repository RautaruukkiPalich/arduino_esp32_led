#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "IButton.h"


// ========== КЛАСС СЕГМЕНТА ==========
class Segment
{
    const int m_id; // Номер сегмента
    const int m_start; // Начальный LED
    const int m_end; // Конечный LED
    const CRGB m_activeColor; // Цвет в активном состоянии
    const CRGB m_defaultColor; // Цвет в неактивном состоянии
    IButton* m_button; // Кнопка
    bool m_isActive; // Активен ли сегмент

public:
    // Конструктор
    Segment(
        int id,
        int start,
        int end,
        CRGB activeColor,
        IButton* button = nullptr,
        CRGB defaultColor = CRGB::White
    );
    ~Segment() = default;

    // Геттеры
    int getId() const { return m_id; }
    int getStart() const { return m_start; }
    int getEnd() const { return m_end; }
    int getLength() const { return m_end - m_start; }
    int getButtonPin() const {return m_button?m_button->getPin() : -1;}
    CRGB getActiveColor() const { return m_activeColor; }
    CRGB getDefaultColor() const { return m_defaultColor; }
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
    bool isButtonPressed() const;
};
