#include "LEDController.h"

LEDController::LEDController(CRGB* leds, const int numLeds, IButton* allWhiteButton)
    : m_leds(leds),
      m_numLeds(numLeds),
      m_allWhiteButton(allWhiteButton),
      m_allWhiteMode(false),
      m_isActive(false)
{
}

// Обработать кнопку "все белым"
bool LEDController::handleAllWhiteButton()
{
    if (!(m_allWhiteButton && m_allWhiteButton->isPressed())) { return false; }

    m_allWhiteMode ? activateAllBlack() : activateAllWhite();

    return true;
}

// Включить всю ленту белым
void LEDController::activateAllWhite()
{
    m_isActive = true;
    m_allWhiteMode = true;
    deactivateSegmentsAndRedraw(true);
}

void LEDController::activateAllBlack()
{
    m_isActive = false;
    m_allWhiteMode = false;
    deactivateSegmentsAndRedraw(false);
    fill_solid(m_leds, m_numLeds, CRGB::Black);
}

void LEDController::deactivateSegmentsAndRedraw(const bool redraw)
{
    for (auto& seg : m_segments)
    {
        seg.deactivate();
        if (redraw)
        {
            seg.draw(m_leds);
        }
    }
}

void LEDController::activateSegmentExclusive(const Segment& seg)
{
    for (auto& s : m_segments)
    {
        if (s.getId() != seg.getId())
        {
            s.deactivate();
        }
        s.draw(m_leds);
    }
}

bool LEDController::handleSegments()
{
    for (auto& seg : m_segments)
    {
        if (!seg.isButtonPressed()) { continue; }

        seg.toggle();
        seg.isActive() ? activateSegmentExclusive(seg) : activateAllWhite();

        m_allWhiteMode = !seg.isActive();

        return true;
    }

    return false;
}

// Обновить состояние (вызывать в loop)
void LEDController::update()
{
    if (handleAllWhiteButton() || (m_isActive && handleSegments()))
    {
        FastLED.show();
    }
}

void LEDController::addSegment(const Segment& segment) { m_segments.push_back(segment); }

// Инициализация: настройка пинов и начальное состояние
void LEDController::init() const
{
    // Начальное состояние - всё выключено
    fill_solid(m_leds, m_numLeds, CRGB::Black);
    FastLED.show();
}

// Вывести информацию о сегментах
void LEDController::printInfo() const
{
    Serial.println("=================================");
    Serial.println("LED Controller Configuration:");
    Serial.print("Total LEDs: ");
    Serial.println(m_numLeds);
    Serial.print("Total segments: ");
    Serial.println(m_segments.size());
    Serial.println("Segments:");

    for (const auto& seg : m_segments)
    {
        Serial.print("  [");
        Serial.print(seg.getId());
        Serial.print("] LEDs ");
        Serial.print(seg.getStart());
        Serial.print("-");
        Serial.print(seg.getEnd() - 1);
        Serial.print(" (");
        Serial.print(seg.getLength());
        Serial.print(" LEDs) | Pin: GPIO");
        Serial.print(seg.getButtonPin());
        Serial.print(" | Active: ");
        Serial.print(seg.isActive() ? "YES" : "NO");
        Serial.print(" | Color: ");
        const CRGB c = seg.getActiveColor();
        Serial.print(c.r);
        Serial.print(",");
        Serial.print(c.g);
        Serial.print(",");
        Serial.println(c.b);
    }

    if (m_allWhiteButton)
    {
        Serial.print("All White Button: GPIO");
        Serial.println(m_allWhiteButton->getPin());
    }
    Serial.println("=================================");
}
