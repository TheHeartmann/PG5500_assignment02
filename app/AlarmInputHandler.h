#pragma once

#include <Arduino.h>
#include <Keypad.h>
#include "AlarmDisplay.h"
#include "TimeDivision.h"

class AlarmInputHandler
{
  public:
    AlarmInputHandler() { reset(); }
    void setAlarmsArray(AlarmDisplay *(*alarmArray)[4]) { alarms = alarmArray; }
    void handleInput(char key)
    {
        if (leader == blank)
        {
            handleNoLeader(key);
        }
        else
        {
            handleModified(key);
            leader = blank;
        }
    }

  private:
    void switchTarget()
    {
        assignValue();
        currentTarget = (TimeDivision)(1 - currentTarget);
        updateAlarm();
    }

    void registerNumeral(const char num)
    {
        temp += String(num);

        if (temp.length() < 2)
        {
            updateAlarmTemp();
            return;
        }

        assignValue();
        updateAlarm();
    }

    void assignValue()
    {
        if (currentTarget == TimeDivision::Hour)
        {
            if (temp.toInt() < 24)
                hours = temp;
        }
        else
        {
            if (temp.toInt() < 60)
                minutes = temp;
        }
        temp = "";
    }

    void updateAlarm() const
    {
        currentAlarm->display(hours, minutes, currentTarget);
    }

    void updateAlarmTemp() const
    {
        if (currentTarget == TimeDivision::Hour)
        {
            currentAlarm->display(temp, minutes, currentTarget);
        }
        else
        {
            currentAlarm->display(hours, temp, currentTarget);
        }
    }

    void reset()
    {
        currentTarget = TimeDivision::Hour;
        hours = minutes = temp = "";
        leader = blank;
    }

    bool isModifier(char c) const { return c == set || c == turnOff; }

    void handleNoLeader(char key)
    {
        if (isAlpha(key))
        {
            const auto desiredAlarm = (*alarms)[key - 'A'];
            if (!editingAlarm || !currentAlarm || currentAlarm != desiredAlarm)
            {
                desiredAlarm->toggle();
            }
        }
        else if (key == set || key == turnOff)
        {
            leader = key;
        }
        else if (isDigit(key) && editingAlarm)
        {
            registerNumeral(key);
        }
    }

    void handleModified(char key)
    {
        if (leader == set)
        {
            if (isModifier(key))
            {
                if (key == set)
                {
                    currentAlarm->save(hours, minutes);
                }
                else if (key == turnOff)
                {
                    currentAlarm->cancel();
                }
                editingAlarm == false;
            }
            else if (isAlpha(key))
            {
                reset();
                if (currentAlarm)
                {
                    currentAlarm->cancel();
                }
                currentAlarm = (*alarms)[key - 'A'];
                currentAlarm->edit(currentTarget);
                editingAlarm = true;
            }
        }
        else if (leader == turnOff)
        {
            if (isAlpha(key))
            {
                (*alarms)[key - 'A']->turnOff();
            }
            else if (key == turnOff && editingAlarm)
            {
                switchTarget();
            }
        }
    }

    String hours;
    String minutes;
    String temp;
    TimeDivision currentTarget = TimeDivision::Hour;

    AlarmDisplay *(*alarms)[4];
    AlarmDisplay *currentAlarm;
    const char set = '#';
    const char turnOff = '*';
    const char blank = '_';

    char leader = blank;
    bool editingAlarm = false;
};
