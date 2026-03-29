#pragma once

#include <Arduino.h>
#include <FastLED.h>

enum Mode{DEFAULT_MODE, ACTIVE_MODE, INACTIVE_MODE};

// ========== КЛАСС СЕГМЕНТА ==========
class Segment
{
    const int m_id; // Номер сегмента
    const int m_start; // Начальный LED
    const int m_end; // Конечный LED
    const CRGB m_activeColor; // Цвет в активном состоянии
    const CRGB m_inactiveColor; // Цвет в активном состоянии
    const CRGB m_defaultColor; // Цвет в неактивном состоянии
    Mode m_mode; // Активен ли сегмент

public:
    // Конструктор
    Segment(
        int id,
        int start,
        int end,
        CRGB activeColor = CRGB::White,
        CRGB inactiveColor = CRGB::Yellow,
        CRGB defaultColor = CRGB::White,
        Mode mode = DEFAULT_MODE
    );
    ~Segment() = default;

    // Геттеры
    int getId() const { return m_id; }
    int getStart() const { return m_start; }
    int getEnd() const { return m_end; }
    int getLength() const { return m_end - m_start; }
    CRGB getActiveColor() const { return m_activeColor; }
    CRGB getInactiveColor() const { return m_inactiveColor; }
    CRGB getDefaultColor() const { return m_defaultColor; }
    Mode getMode() const { return m_mode; }

    // Управление состоянием
    void setMode(const Mode mode) { m_mode = mode; }

    // Получить текущий цвет (активный или дефолтный)
    CRGB getCurrentColor() const;
};
