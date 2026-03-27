#pragma once

#include <FastLED.h>

#include "IButton.h"

class DigitalButton final : public IButton
{
    const int m_pin;
    unsigned long m_lastDebounce = 0;
    static constexpr unsigned long DEBOUNCE_DELAY = 200;

    void printInfo() const
    {
        Serial.print("DigitalButton: ");
        Serial.print(m_pin);
        Serial.print(". ");
        Serial.println("Pressed");
    }

public:
    explicit DigitalButton(const int pin) : m_pin(pin)
    {
        pinMode(m_pin, INPUT_PULLUP);
    }

    bool isPressed() override
    {
        if (digitalRead(m_pin) != LOW){return false;}  // LOW для нажатой кнопки с PULLUP

        const unsigned long now = millis();
        if (now - m_lastDebounce < DEBOUNCE_DELAY){return false;}

        m_lastDebounce = now;

        printInfo();

        return true;
    }

    int getPin() const override { return m_pin; }
};
