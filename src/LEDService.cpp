#include "LEDService.h"

LEDService::LEDService(
    CRGB* leds,
    const int numLeds)
    :
    m_leds(leds),
    m_numLeds(numLeds)
{
    activateBlackMode();
}

void LEDService::addSegment(const Segment& s)
{
    m_segments.push_back(s);
}


void LEDService::handleMainButton()
{
    m_isActive && m_whiteMode ? activateBlackMode() : activateWhiteMode();

    FastLED.show();
}

void LEDService::handleSegmentButton(const int segId)
{
    if (!m_isActive)
    {
        return;
    }
    const Segment* s = getSegmentById(segId);
    if (!s)
    {
        Serial.println("Segment not found with id: ");
        Serial.println(segId);
        return;
    }

    switch (s->getMode())
    {
    case ACTIVE_MODE:
        m_whiteMode = true;

        setModeAndRedrawSegments(DEFAULT_MODE, true);
        break;
    default:
        m_whiteMode = false;

        activateExecutiveSegment(s);
        break;
    }

    FastLED.show();
}

void LEDService::activateWhiteMode()
{
    m_isActive = true;
    m_whiteMode = true;
    setModeAndRedrawSegments(DEFAULT_MODE, true);
}

void LEDService::activateBlackMode()
{
    m_isActive = false;
    m_whiteMode = false;
    setModeAndRedrawSegments(DEFAULT_MODE, false);
    fill_solid(m_leds, m_numLeds, CRGB::Black);
}

Segment* LEDService::getSegmentById(const int id)
{
    for (Segment& segment : m_segments)
    {
        if (segment.getId() == id)
        {
            return &segment;
        }
    }

    return nullptr;
}

void LEDService::activateExecutiveSegment(const Segment* s)
{
    for (Segment& seg : m_segments)
    {
        if (seg.getId() == s->getId())
        {
            setModeAndRedrawSegment(seg, ACTIVE_MODE, true);
        }
        else
        {
            setModeAndRedrawSegment(seg, INACTIVE_MODE, true);
        }
    }
}

void LEDService::setModeAndRedrawSegments(const Mode mode, const bool redraw)
{
    for (Segment& s : m_segments)
    {
        setModeAndRedrawSegment(s, mode, redraw);
    }
}

void LEDService::setModeAndRedrawSegment(Segment& s, const Mode mode, const bool redraw) const
{
    s.setMode(mode);
    if (redraw){draw(s);}
}

void LEDService::draw(const Segment& s) const
{
    const CRGB color = s.getCurrentColor();
    for (int i = s.getStart(); i < s.getEnd(); i++)
    {
        m_leds[i] = color;
    }
}

void LEDService::printInfo() const
{
    Serial.println("=================================");
    Serial.println("LED Service Configuration:");
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
        Serial.print(" LEDs)");
        Serial.print(" | Mode: ");
        Serial.print(seg.getMode());
        Serial.print(" | Color: ");
        const CRGB c = seg.getActiveColor();
        Serial.print(c.r);
        Serial.print(",");
        Serial.print(c.g);
        Serial.print(",");
        Serial.println(c.b);
    }
    Serial.println("=================================");
}

