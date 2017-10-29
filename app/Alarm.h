#pragma once

#include <Arduino.h>
#include <TFT.h>
#include "TextOptions.h"
#include <RTClib.h>
#include "RGB.h"
#include "TextSection.h"
#include "TimeDisplay.h"
#include "Pins.h"

class Alarm : public TimeDisplay {
public:
  Alarm(TFT &tft, RTC_DS1307 rtc, const short textSize, const Vector hourPos)
  : TimeDisplay(tft, rtc, textSize, hourPos) {}
  void update() override;
  void set(DateTime *newTime);

  void toggle();

private:
  void ring() const;
  void turnOff() const;
  void display(DateTime *newTime) const;

  bool active;
  RGB textColor = WHITE;
  DateTime alarmTime;
};