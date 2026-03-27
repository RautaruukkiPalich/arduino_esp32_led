#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include <vector>
#include "Segment.h"
#include <algorithm>

class LEDController
{
    CRGB* m_leds; // Указатель на массив светодиодов
    int m_numLeds; // Количество светодиодов в ленте
    std::vector<Segment> m_segments; // Вектор сегментов
    IButton* m_allWhiteButton; // Пин кнопки "все белым"
    bool m_allWhiteMode; // Режим "вся лента белым"
    bool m_isActive; // Включена ли лента

    // Обработать кнопку "все белым"
    bool handleAllWhiteButton();
    // Обработать кнопки и состояние сегментов
    bool handleSegments();

    void activateAllWhite();
    void activateAllBlack();
    void activateSegmentExclusive(const Segment& seg);

    void deactivateSegmentsAndRedraw(bool redraw);

public:
    LEDController(CRGB* leds, int numLeds, IButton* allWhiteButton);

    // Добавить сегмент (вызывать в setup)
    void addSegment(const Segment& segment);
    // Обновить состояние (вызывать в loop)
    void update();
    // Инициализация: настройка пинов и начальное состояние
    void init() const;
    // Вывести информацию о сегментах
    void printInfo() const;
};
