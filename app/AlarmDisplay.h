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

class AlarmDisplay : public TimeDisplay
{
  public:
    AlarmDisplay(TFT &tft, RTC_DS1307 rtc, const short textSize, const Vector hourPos)
        : TimeDisplay(tft, rtc, textSize, hourPos) {}
    void update() const override;
    void set(DateTime *newTime);
    void init() const override;

    void display(const String &hours, const String &minutes) const;
    void turnOff() const;
    void toggle();

  private:
    void setActive(bool activeState);

    bool active;
    String hourString, minuteString;
    const RGB INACTIVE_COLOR = RED;
    const RGB ACTIVE_COLOR = GREEN;
    const RGB EDITING_COLOR = ORANGE;
    DateTime alarmTime;
};

void ring();