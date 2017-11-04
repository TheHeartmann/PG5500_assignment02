#include <RTClib.h>
#include <SPI.h>
#include <SimpleTimer.h>
#include <TFT.h> // Arduino LCD library

#include "AlarmDisplay.h"
#include "InputHandler.h"
#include "Pins.h"
#include "RGB.h"
#include "TextOptions.h"
#include "TextSection.h"
#include "TimeKeeper.h"
#include "Vector.h"

// RTC
RTC_DS1307 rtc;

// TFT
TFT tft = TFT(cs, dc, rst);
SimpleTimer timer;
auto tk = TimeKeeper(tft, rtc);
auto alarmA = AlarmDisplay(tft, rtc, 2, {0, 60});
auto alarmB = AlarmDisplay(tft, rtc, 2, {90, 60});
auto alarmC = AlarmDisplay(tft, rtc, 2, {0, 80});
auto alarmD = AlarmDisplay(tft, rtc, 2, {90, 80});
AlarmDisplay *alarms[] = {&alarmA, &alarmB, &alarmC, &alarmD};
auto input = InputHandler(&alarms);

void setup()
{
    if (!rtc.begin()) { while (1) ; }

    tft.begin();
    tft.background(0, 0, 0);

    tk.init();

    for (auto &i : alarms) {
        i->init();
    }

    tick();
    timer.setInterval(1000, tick);
}

void tick()
{
    tk.update();
}

void loop()
{
    timer.run();
    input.readInput();
}