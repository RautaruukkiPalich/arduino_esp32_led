#include <Arduino.h>
#include <FastLED.h>

#include "AnalogButton.h"
#include "ButtonController.h"
#include "Segment.h"
#include "LEDService.h"

// ========== НАСТРОЙКИ ЛЕНТЫ ==========
#define LED_PIN     5
#define NUM_LEDS    256
#define BRIGHTNESS  200 //0-255
#define LED_TYPE    WS2812B

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

CRGB leds[NUM_LEDS];
LEDService* ledService;
ButtonController* buttonController;

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

    ledService = new LEDService(leds, NUM_LEDS);
    ledService->addSegment(Segment(0, 8, 42,
        CRGB::White, CRGB::White, CRGB::White));
    ledService->addSegment(Segment(1, 43, 76));
    ledService->addSegment(Segment(2, 78, 109));
    ledService->addSegment(Segment(3, 110, 131));
    ledService->addSegment(Segment(4, 132, 165));
    ledService->addSegment(Segment(5, 166, 189));
    ledService->addSegment(Segment(6, 190, 221));
    ledService->addSegment(Segment(7, 223, 254));

    ledService->printInfo();

    buttonController = new ButtonController();
    buttonController->addButton(&btnAll, std::bind(&LEDService::handleMainButton, ledService));
    buttonController->addButton(&btn1, std::bind(&LEDService::handleSegmentButton, ledService, 1));
    buttonController->addButton(&btn2, std::bind(&LEDService::handleSegmentButton, ledService, 2));
    buttonController->addButton(&btn3, std::bind(&LEDService::handleSegmentButton, ledService, 3));
    buttonController->addButton(&btn4, std::bind(&LEDService::handleSegmentButton, ledService, 4));
    buttonController->addButton(&btn5, std::bind(&LEDService::handleSegmentButton, ledService, 5));
    buttonController->addButton(&btn6, std::bind(&LEDService::handleSegmentButton, ledService, 6));
    buttonController->addButton(&btn7, std::bind(&LEDService::handleSegmentButton, ledService, 7));

    buttonController->printInfo();

    Serial.println("Ready! Press buttons to control LEDs");
}

void loop()
{
    buttonController->update();
    delay(75);
}
