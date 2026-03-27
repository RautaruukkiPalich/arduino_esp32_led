#pragma once

#include <FastLED.h>

#include "IButton.h"

class AnalogButton final: public IButton
{
    const int m_pin;
    unsigned long m_lastDebounce = 0;
    static constexpr unsigned long DEBOUNCE_DELAY = 200;

    void printInfo() const
    {
        Serial.print("AnalogButton: ");
        Serial.print(m_pin);
        Serial.print(". ");
        Serial.println("Pressed");
    }

public:
    explicit AnalogButton(const int pin): m_pin(pin)
    {
        pinMode(m_pin, INPUT_PULLDOWN);
    }

    bool isPressed() override
    {
        if (digitalRead(m_pin) != HIGH) { return false; }

        const unsigned long now = millis();
        if (now - m_lastDebounce < DEBOUNCE_DELAY) { return false; }

        m_lastDebounce = now;

        printInfo();

        return true;
    }

    int getPin() const override { return m_pin; }
};
