#include "ButtonController.h"
#include <memory>

void ButtonController::addButton(const ButtonMapping& btn)
{
    if (btn.m_Button != nullptr)
    {
        m_buttons.push_back(btn);
    }
}

void ButtonController::addButton(IButton* btn, std::function<void()> callback)
{
    if (btn != nullptr)
    {
        m_buttons.push_back({btn, std::move(callback)});
    }
}

void ButtonController::update() const
{
    for (const ButtonMapping& ctrl : m_buttons)
    {
        if (ctrl.m_Button && ctrl.m_Button->isPressed())
        {
            ctrl.callback();
            return;
        }
    }
}

void ButtonController::printInfo() const
{
    Serial.println("=================================");
    Serial.println("Button Controller Configuration:");
    Serial.print("Total buttons: ");
    Serial.println(m_buttons.size());
}
