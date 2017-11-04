#include "AlarmDisplay.h"

void AlarmDisplay::update() const
{
    display(hourString, minuteString);
}

void AlarmDisplay::display(const String &newHour, const String &newMinutes) const
{
    const auto hourPadded = pad(newHour.toInt());
    const auto minutesPadded = pad(newMinutes.toInt());

    minutes.update(hourPadded, &currentColor);
    hour.update(minutesPadded, &currentColor);
}

void AlarmDisplay::display(const String &newHour, const String &newMinutes, const TimeDivision target) const
{
    const auto hourPadded = pad(newHour.toInt());
    const auto minutesPadded = pad(newMinutes.toInt());

    redrawForEdit(hourPadded, minutesPadded, target);
}

void AlarmDisplay::toggle()
{
    active = !active;
    currentColor = active ? ACTIVE_COLOR : INACTIVE_COLOR;
    redraw();
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

void AlarmDisplay::save(const String hours, const String minutes)
{
    hourString = pad(hours.toInt());
    minuteString = pad(minutes.toInt());
    set();
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

void AlarmDisplay::set() const
{
    // Alarm.alarmRepeat((int)hourString.toInt(), (int)minuteString.toInt(), 0, ring);
}

void AlarmDisplay::turnOff() const {}

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

void AlarmDisplay::ring() {}