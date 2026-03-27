#include <Arduino.h>
#include <FastLED.h>

#include "AnalogButton.h"
#include "Segment.h"
#include "LEDController.h"

// ========== НАСТРОЙКИ ЛЕНТЫ ==========
#define LED_PIN     5
#define NUM_LEDS    256
#define BRIGHTNESS  150 //0-255
#define LED_TYPE    WS2812B

CRGB leds[NUM_LEDS];
LEDController* controller;

// ========== ПИНЫ КНОПОК ==========
#define BTN_ALL     13

// Игроки 1-7
#define BTN_SEG1    12
#define BTN_SEG2    14
#define BTN_SEG3    27
#define BTN_SEG4    26
#define BTN_SEG5    25
#define BTN_SEG6    33
#define BTN_SEG7    32

AnalogButton btnAll(BTN_ALL);
AnalogButton btn1(BTN_SEG1);
AnalogButton btn2(BTN_SEG2);
AnalogButton btn3(BTN_SEG3);
AnalogButton btn4(BTN_SEG4);
AnalogButton btn5(BTN_SEG5);
AnalogButton btn6(BTN_SEG6);
AnalogButton btn7(BTN_SEG7);

void setup()
{
    Serial.begin(115200);
    delay(100);

    FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    controller = new LEDController(leds, NUM_LEDS, &btnAll);

    controller->addSegment(Segment(0, 8, 42, CRGB::White));
    controller->addSegment(Segment(1, 43, 76, CRGB::Cyan, &btn1));
    controller->addSegment(Segment(2, 78, 109, CRGB::Cyan, &btn2));
    controller->addSegment(Segment(3, 110, 131, CRGB::Cyan, &btn3));
    controller->addSegment(Segment(4, 132, 165, CRGB::Cyan, &btn4));
    controller->addSegment(Segment(5, 166, 189, CRGB::Cyan, &btn5));
    controller->addSegment(Segment(6, 190, 221, CRGB::Cyan, &btn6));
    controller->addSegment(Segment(7, 223, 254, CRGB::Cyan, &btn7));

    controller->init();

    controller->printInfo();

    Serial.println("Ready! Press buttons to control LEDs");
}

void loop()
{
    controller->update();
    delay(75);
}
