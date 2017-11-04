#pragma once

#include <Arduino.h>
#include <TFT.h>
#include "TextOptions.h"
#include <RTClib.h>
#include "RGB.h"
#include "TextSection.h"
#include "TimeDisplay.h"

class TimeKeeper : public TimeDisplay
{
  public:
    TimeKeeper(TFT &tft, RTC_DS1307 &rtc);
    void update() const override;

  private:
    String getDateString(const DateTime &now) const;

    char daysOfTheWeek[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // char arrays to print to the screen
    char DATE[15];
    char SECS[3];

    // text sizes
    // text width is 60% of height
    const short DATE_SIZE = 1;
    const short HOUR_SIZE = 4;
    const short SECOND_SIZE = 2;

    TextSection date, seconds;
};
