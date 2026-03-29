#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include <functional>
#include <vector>
#include <memory>

#include "IButton.h"
#include "LEDService.h"

struct ButtonMapping
{
    IButton* m_Button;
    std::function<void()> callback;
};

class ButtonController
{
    std::vector<ButtonMapping> m_buttons;

public:
    ButtonController() = default;
    ~ButtonController() = default;

    void addButton(const ButtonMapping& btn);
    void addButton(IButton* btn, std::function<void()> callback);
    void update() const;
    void printInfo() const;
};
