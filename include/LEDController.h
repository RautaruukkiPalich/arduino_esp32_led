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
    int m_allWhiteButtonPin; // Пин кнопки "все белым"
    bool m_allWhiteMode; // Режим "вся лента белым"
    bool m_isActive; // Включена ли лента
    unsigned long m_lastAllWhiteDebounce; // Антидребезг для белой кнопки
    static constexpr unsigned long DEBOUNCE_DELAY = 200;

    // Проверить, есть ли активные сегменты
    bool hasActiveSegments() const;

    // Обновить режим белого (если есть активные сегменты - отключаем белый)
    void updateWhiteMode();

    // Обработать кнопку "все белым"
    void handleAllWhiteButton();

    void activateAllBlack();

    bool handleSegments();

public:
    LEDController(CRGB* leds, int numLeds, int allWhiteButtonPin);

    void addSegment(const Segment& segment);
    // Включить всю ленту белым
    void activateAllWhite();
    // Обновить состояние (вызывать в loop)
    void update();
    // Инициализация: настройка пинов и начальное состояние
    void init() const;
    // Вывести информацию о сегментах
    void printInfo() const;
};
