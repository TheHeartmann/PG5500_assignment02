#include "Alarm.h"

void Alarm::update()
{
    if (!active)
        return;

    auto now = rtc.now();

    if (now.hour() == alarmTime.hour() && now.minute() == alarmTime.minute()) {

    }
    // if (rtc.now() != alarmTime) return;
    static int prevHour, prevMin;
    auto currentHour = now.hour();
    auto currentMinute = now.minute();

    if (currentMinute != prevMin)
    {
        auto ms = pad(currentMinute);
        minutes.update(&ms);
        if (currentHour != prevHour)
        {
            auto hs = pad(currentHour);
            hour.update(&hs);
        }
    }

    prevHour = currentHour;
    prevMin = currentMinute;
}

void Alarm::display(DateTime *newTime) const {
    auto newHour = pad(newTime->hour());
    auto newMinutes = pad(newTime->minute());

    hour.update(&newHour);
    minutes.update(&newMinutes);
}

void Alarm::toggle() {
    active = !active;
}

void Alarm::set(DateTime *newTime)
{
    alarmTime = *newTime;
    display(&alarmTime);
}


void Alarm::ring() const {}

void Alarm::turnOff() const {}