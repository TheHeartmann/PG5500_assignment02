#include "AlarmDisplay.h"

void AlarmDisplay::update() const
{
    display(hourString, minuteString);
}

void AlarmDisplay::display(const String &newHour, const String &newMinutes) const
{
    const auto hourPadded = pad(newHour.toInt());
    const auto minutesPadded = pad(newMinutes.toInt());

    hour.update(hourPadded, &currentColor);
    minutes.update(minutesPadded, &currentColor);
}

void AlarmDisplay::display(const String &newHour, const String &newMinutes, const TimeDivision target) const
{
    const auto hourPadded = pad(newHour.toInt());
    const auto minutesPadded = pad(newMinutes.toInt());

    redrawForEdit(hourPadded, minutesPadded, target);
}

void AlarmDisplay::toggle(bool updateDisplay)
{
    active = !active;
    currentColor = active ? ACTIVE_COLOR : INACTIVE_COLOR;
    if (updateDisplay)
    {
        redraw();
    }
}

void AlarmDisplay::toggle()
{
    toggle(true);
}

void AlarmDisplay::edit(const TimeDivision target) const
{
    redrawForEdit(hourString, minuteString, target);
}

void AlarmDisplay::redrawForEdit(const String hourPadded, const String minutesPadded, const TimeDivision target) const
{
    const auto hourColor = target == TimeDivision::Hour ? EDITING_COLOR : EDITING_INACTIVE;
    const auto minuteColor = target == TimeDivision::Minutes ? EDITING_COLOR : EDITING_INACTIVE;

    hour.update(hourPadded, &hourColor);
    minutes.update(minutesPadded, &minuteColor);
}

void AlarmDisplay::set(const String hours, const String minutes)
{
    hourString = pad(hours.toInt());
    minuteString = pad(minutes.toInt());
    update();
}

void AlarmDisplay::cancel() const
{
    display(hourString, minuteString);
}

void AlarmDisplay::redraw() const
{
    redraw(&currentColor);
}

void AlarmDisplay::redraw(const RGB *color) const
{
    hour.redraw(color);
    minutes.redraw(color);
}

void AlarmDisplay::turnOff()
{
    noTone(ALARM_PIN);
}

void AlarmDisplay::init() const
{
    TimeDisplay::init();
    currentColor = INACTIVE_COLOR;
    hourString = "00";
    minuteString = "00";
    const auto unset = String("--");
    minutes.update(unset, &currentColor);
    hour.update(unset, &currentColor);
}

const String &AlarmDisplay::getHours() const
{
    return hourString;
}

const String &AlarmDisplay::getMins() const
{
    return minuteString;
}

void AlarmDisplay::ring() const
{
    tone(ALARM_PIN, ALARM_TONE);
}

void AlarmDisplay::checkAlarm() const
{
    if (!active)
    {
        return;
    }
    const auto now = rtc.now();
    if (now.hour() == hourString.toInt() && now.minute() == minuteString.toInt() && now.second() == 0)
    {
        ring();
    }
}