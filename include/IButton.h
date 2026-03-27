#pragma once

class IButton
{
public:
    virtual ~IButton() = default;
    virtual bool isPressed() = 0;
    virtual int getPin() const = 0;
};
