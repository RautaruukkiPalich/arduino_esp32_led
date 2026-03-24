#include "LEDController.h"

LEDController::LEDController(CRGB* leds, int numLeds, const int allWhiteButtonPin)
    : m_leds(leds),
      m_numLeds(numLeds),
      m_allWhiteButtonPin(allWhiteButtonPin),
      m_allWhiteMode(false),
      m_lastAllWhiteDebounce(0)
{
}

bool LEDController::hasActiveSegments() const
{
    return std::any_of(
        m_segments.begin(),
        m_segments.end(),
        [](const Segment& seg)
        {
            return seg.isActive();
        });
}

// Обновить режим белого (если есть активные сегменты - отключаем белый)
void LEDController::updateWhiteMode()
{
    if (m_allWhiteMode && hasActiveSegments())
    {
        m_allWhiteMode = false;
        // Перерисовываем все сегменты
        for (auto& seg : m_segments)
        {
            seg.draw(m_leds);
        }
    }
}

// Обработать кнопку "все белым"
void LEDController::handleAllWhiteButton()
{
    if (digitalRead(m_allWhiteButtonPin) != HIGH) { return; }

    const unsigned long now = millis();
    if (now - m_lastAllWhiteDebounce > DEBOUNCE_DELAY)
    {
        m_lastAllWhiteDebounce = now;
        activateAllWhite();
    }
}


void LEDController::addSegment(const Segment& segment) { m_segments.push_back(segment); }

// Включить всю ленту белым
void LEDController::activateAllWhite()
{
    m_allWhiteMode = true;

    // Вся лента белая
    // fill_solid(m_leds, NUM_LEDS, CRGB::White);

    // Деактивируем все сегменты
    for (auto& seg : m_segments)
    {
        seg.deactivate();
        seg.draw(m_leds);
    }

    FastLED.show();
}

// Обновить состояние (вызывать в loop)
void LEDController::update()
{
    // Обрабатываем кнопку "все белым"
    handleAllWhiteButton();

    // Обрабатываем кнопки сегментов
    bool needUpdate = false;

    for (auto& seg : m_segments)
    {
        if (!seg.isButtonPressed()) { continue; }

        seg.toggle();

        // Если включили сегмент - выключаем белый режим
        if (seg.isActive() && m_allWhiteMode)
        {
            m_allWhiteMode = false;
            // Перерисовываем все сегменты
            for (auto& s : m_segments)
            {
                s.draw(m_leds);
            }
        }
        else
        {
            // Перерисовываем только этот сегмент
            seg.draw(m_leds);
        }

        needUpdate = true;
    }

    // Проверяем, нужно ли отключить белый режим
    updateWhiteMode();

    // Если были изменения, обновляем ленту
    if (needUpdate || m_allWhiteMode)
    {
        FastLED.show();
    }
}

// Инициализация: настройка пинов и начальное состояние
void LEDController::init() const
{
    // Настройка пинов для кнопок
    pinMode(m_allWhiteButtonPin, INPUT_PULLDOWN);
    for (const auto& seg : m_segments)
    {
        pinMode(seg.getButtonPin(), INPUT_PULLDOWN);
    }

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
        CRGB c = seg.getActiveColor();
        Serial.print(c.r);
        Serial.print(",");
        Serial.print(c.g);
        Serial.print(",");
        Serial.println(c.b);
    }

    Serial.print("All White Button: GPIO");
    Serial.println(m_allWhiteButtonPin);
    Serial.println("=================================");
}
