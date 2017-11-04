#include "AlarmDisplay.h"

void AlarmDisplay::update() const
{
    auto now = rtc.now();

    static int prevHour, prevMin;
    auto currentHour = now.hour();
    auto currentMinute = now.minute();

    if (currentMinute != prevMin)
    {
        auto ms = pad(currentMinute);
        minutes.update(ms);
        if (currentHour != prevHour)
        {
            auto hs = pad(currentHour);
            hour.update(hs);
        }
    }

    prevHour = currentHour;
    prevMin = currentMinute;
}

void AlarmDisplay::display(const String &newHour, const String &newMinutes) const
{
    const auto hourPadded = pad(newHour.toInt());
    const auto minutesPadded = pad(newMinutes.toInt());

    hour.update(hourPadded);
    minutes.update(minutesPadded);
}

void AlarmDisplay::toggle()
{
    active = !active;
    const auto color = active ? ACTIVE_COLOR : INACTIVE_COLOR;
    hour.redraw(&color);
    minutes.redraw(&color);
}

void AlarmDisplay::set(DateTime *newTime)
{
    alarmTime = *newTime;
    Alarm.alarmRepeat((int)hourString.toInt(), (int)minuteString.toInt(), 0, ring);
    // change color of alarm using the 1 - enum method
}

void AlarmDisplay::turnOff() const {}

void AlarmDisplay::init() const {
    TimeDisplay::init();
    const auto unset = String("--");
    minutes.update(unset, &INACTIVE_COLOR);
    hour.update(unset, &INACTIVE_COLOR);
}