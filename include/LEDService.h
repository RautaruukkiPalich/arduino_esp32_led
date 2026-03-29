#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include "Segment.h"
#include <vector>

class LEDService
{
    CRGB* m_leds = nullptr; // Указатель на массив светодиодов
    int m_numLeds = 0; // Количество светодиодов в ленте

    std::vector<Segment> m_segments = std::vector<Segment>(); // Вектор сегментов

    bool m_whiteMode = false; // Режим "вся лента белым"
    bool m_isActive = false; // Включена ли лента

    void activateWhiteMode();
    void activateBlackMode();

    void setModeAndRedrawSegments(Mode mode, bool redraw);
    void setModeAndRedrawSegment(Segment& s, Mode mode, bool redraw) const;
    void draw(const Segment& s) const;

    void activateExecutiveSegment(const Segment* segment);
    Segment* getSegmentById(int id);

public:
    LEDService(CRGB* leds, int numLeds);
    ~LEDService() = default;

    void addSegment(const Segment& s);

    void handleMainButton();
    void handleSegmentButton(int segId);

    void printInfo() const;
};
