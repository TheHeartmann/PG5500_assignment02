#pragma once

#include <Arduino.h>
#include <TFT.h>
#include "TextOptions.h"
#include <RTClib.h>
#include "RGB.h"
#include "TextSection.h"

class TimeKeeper
{
  public:
    TimeKeeper(TFT &tft, RTC_DS1307 &rtc) : tft(tft), rtc(rtc){}
    void updateTime();
    void writeSeparator() const;

  private:
    String getDateString(const DateTime &now) const;
    String pad(int number) const;

    RTC_DS1307 &rtc;
    TFT &tft;
    char daysOfTheWeek[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // char arrays to print to the screen
    char DATE[15];
    char HH[3];
    char MM[3];
    char SECS[3];
    const char SEPARATOR[2] = {':', '\0'};

    // text sizes
    // text width is 60% of height
    const short DATE_SIZE = 1;
    const short HOUR_SIZE = 4;
    const short SECOND_SIZE = 2;

    const Vector RESOLUTION = {tft.width(), tft.height()};

    // text coordinates
    const Vector DATE_POS = {0, RESOLUTION.y - DATE_SIZE * 10};
    const short HOUR_Y = 20;
    const Vector HOUR_POS = {0, HOUR_Y};
    const Vector MINUTES_POS = {HOUR_POS.x + 3 * HOUR_SIZE * 6, HOUR_Y};
    const Vector SECONDS_POS = {HOUR_POS.x + 5 * HOUR_SIZE * 6 + 5, HOUR_Y + 15};

    const TextOptions DATE_OPTS = TextOptions{DATE_POS, DATE_SIZE, 15};
    const TextOptions HOUR_OPTS = TextOptions{HOUR_POS, HOUR_SIZE, 3};
    const TextOptions MIN_OPTS = TextOptions{MINUTES_POS, HOUR_SIZE, 3};
    const TextOptions SEC_OPTS = TextOptions{SECONDS_POS, SECOND_SIZE, 3};

    // text section objects
    TextSection date = TextSection(tft, DATE_OPTS, DATE);
    TextSection hour = TextSection(tft, HOUR_OPTS, HH);
    TextSection minutes = TextSection(tft, MIN_OPTS, MM);
    TextSection seconds = TextSection(tft, SEC_OPTS, SECS);
};
