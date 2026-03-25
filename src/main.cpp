#include <Arduino.h>
#include <FastLED.h>
#include "Segment.h"
#include "LEDController.h"

// ========== НАСТРОЙКИ ЛЕНТЫ ==========
#define LED_PIN     5
#define NUM_LEDS    256
#define BRIGHTNESS  150 //0-255
#define LED_TYPE    WS2812B

// ========== ПИНЫ КНОПОК ==========
#define BTN_ALL     13

// Ведущий, не управляется
#define BTN_SEG_VED    34

// Игроки 1-7
#define BTN_SEG1    12
#define BTN_SEG2    14
#define BTN_SEG3    27
#define BTN_SEG4    26
#define BTN_SEG5    25
#define BTN_SEG6    33
#define BTN_SEG7    32

CRGB leds[NUM_LEDS];
LEDController* controller;

void setup()
{
    Serial.begin(115200);
    delay(100);

    FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    controller = new LEDController(leds, NUM_LEDS, BTN_ALL);

    controller->addSegment(Segment(0, 8, 42, CRGB::White, BTN_SEG_VED));
    controller->addSegment(Segment(1, 43, 76, CRGB::Cyan, BTN_SEG1));
    controller->addSegment(Segment(2, 78, 109, CRGB::Cyan, BTN_SEG2));
    controller->addSegment(Segment(3, 110, 131, CRGB::Cyan, BTN_SEG3));
    controller->addSegment(Segment(4, 132, 165, CRGB::Cyan, BTN_SEG4));
    controller->addSegment(Segment(5, 166, 189, CRGB::Cyan, BTN_SEG5));
    controller->addSegment(Segment(6, 190, 221, CRGB::Cyan, BTN_SEG6));
    controller->addSegment(Segment(7, 223, 254, CRGB::Cyan, BTN_SEG7));

    controller->init();

    controller->printInfo();

    Serial.println("Ready! Press buttons to control LEDs");
}

void loop()
{
    controller->update();
    delay(75);
}
