#pragma once

#include <Arduino.h>
#include <TFT.h>
#include "TextOptions.h"
#include <RTClib.h>
#include "RGB.h"
#include "TextSection.h"
#include "Vector.h"

class TimeDisplay {
  public:
    TimeDisplay(TFT &tft, RTC_DS1307 &rtc, const short textSize, const Vector hourPos, char separator = ':');
    virtual void init() const;
    virtual void update() const = 0;

  protected:
    String pad(int number) const;

    RTC_DS1307 &rtc;
    TFT *tft;

    char HH[3];
    char MM[3];
    char SEPARATOR[2];

    const short SIZE;
    const Vector HOUR_POS;
    const Vector MIN_POS;
    const Vector SEP_POS;
    const Vector RESOLUTION = {tft->width(), tft->height()};
    const char SEP;
    TextSection hour, minutes, separator;
};