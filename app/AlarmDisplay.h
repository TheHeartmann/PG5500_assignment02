#pragma once

#include <Arduino.h>
#include <RTClib.h>
#include <TFT.h>
#include <TimeAlarms.h>

#include "Pins.h"
#include "RGB.h"
#include "TextOptions.h"
#include "TextSection.h"
#include "TimeDisplay.h"
#include "TimeDivision.h"

class AlarmDisplay : public TimeDisplay
{
  public:
    AlarmDisplay(TFT &tft, RTC_DS1307 rtc, const short textSize, const Vector hourPos)
        : TimeDisplay(tft, rtc, textSize, hourPos) {}
    void update() const override;
    void init() const override;

    void display(const String &hours, const String &minutes) const;
    void display(const String &hours, const String &minutes, const TimeDivision target) const;
    void turnOff() const;
    void toggle();
    void toggle(bool updateDisplay);
    void edit(const TimeDivision target) const;
    void cancel() const;
    void save(const String hours, const String minutes);
    const String& getMins() const;
    const String& getHours() const;

  private:
    void set() const;
    void redraw(const RGB *color) const;
    void redraw() const;
    void redrawForEdit(const String hourPadded, const String minutesPadded, const TimeDivision target) const;
    void setActive(bool activeState);
    void ring();

    bool active;
    String hourString, minuteString;
    const RGB INACTIVE_COLOR = RED;
    const RGB ACTIVE_COLOR = GREEN;
    const RGB EDITING_COLOR = ORANGE;
    const RGB EDITING_INACTIVE = GRAY;
    RGB currentColor;
};