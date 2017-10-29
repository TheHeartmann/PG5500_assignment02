#include <RTClib.h>
#include <SPI.h>
#include <SimpleTimer.h>
#include <TFT.h> // Arduino LCD library

#include "Alarm.h"
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
auto alarm = Alarm(tft, rtc, 2, {0, 60});
const Alarm alarms[] = {alarm};
const auto input = InputHandler(alarms);
// TimeKeeper tk;

void setup()
{
    // init RTC
    if (!rtc.begin()) { while (1) ; }
    if (!rtc.isrunning())
    {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    tft.begin();
    tft.background(0, 0, 0);
    // tft.background(0, 0, 255);
    updateTk();
    timer.setInterval(1000, updateTk);

    alarm.update();
}

void updateTk()
{
    tk.update();
}

void loop()
{
    timer.run();
    input.readInput();
}