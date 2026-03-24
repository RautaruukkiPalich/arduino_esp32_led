#include <Arduino.h>
#include <FastLED.h>
#include "Segment.h"
#include "LEDController.h"

// ========== НАСТРОЙКИ ЛЕНТЫ ==========
#define LED_PIN     5
#define NUM_LEDS    250
#define BRIGHTNESS  150
#define LED_TYPE    WS2812B

// ========== ПИНЫ КНОПОК ==========
#define BTN_ALL     13
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
// write your initialization code here
{
    Serial.begin(115200);
    delay(100);

    FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    controller = new LEDController(leds, NUM_LEDS, BTN_ALL);

    controller->addSegment(Segment(1, 0, 30, CRGB::Red, BTN_SEG1));
    controller->addSegment(Segment(2, 35, 65, CRGB::Green, BTN_SEG2));
    controller->addSegment(Segment(3, 70, 100, CRGB::Blue, BTN_SEG3));
    controller->addSegment(Segment(4, 105, 135, CRGB::Yellow, BTN_SEG4));
    controller->addSegment(Segment(5, 140, 170, CRGB::Purple, BTN_SEG5));
    controller->addSegment(Segment(6, 175, 205, CRGB::Orange, BTN_SEG6));
    controller->addSegment(Segment(7, 210, 240, CRGB::Cyan, BTN_SEG7));

    controller->init();

    controller->printInfo();

    Serial.println("Ready! Press buttons to control LEDs");
}

void loop()
{
    // write your code here
    controller->update();
    delay(10);
}
