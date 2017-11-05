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
        temp = currentTarget == TimeDivision::Hour ? minutes : hours;
        currentTarget = (TimeDivision)(1 - currentTarget);
        updateAlarm();
    }

    void registerNumeral(const char num)
    {
        if (temp.length() >= 2)
        {
            temp = "";
        }
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
            desiredAlarm->toggle(!currentAlarm || desiredAlarm != currentAlarm);
        }
        else if (key == set || key == turnOff)
        {
            leader = key;
        }
        else if (isDigit(key) && currentAlarm)
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
                    assignValue();
                    currentAlarm->set(hours, minutes);
                }
                else if (key == turnOff)
                {
                    currentAlarm->cancel();
                }
                currentAlarm = nullptr;
            }
            else if (isAlpha(key))
            {
                changeAlarm(key);
            }
        }
        else if (leader == turnOff)
        {
            if (isAlpha(key))
            {
                AlarmDisplay::turnOff();
                // (*alarms)[key - 'A']->turnOff();
            }
            else if (key == turnOff && currentAlarm)
            {
                switchTarget();
            }
        }
    }

    void changeAlarm(char key)
    {
        reset();
        if (currentAlarm)
        {
            currentAlarm->cancel();
        }
        currentAlarm = (*alarms)[key - 'A'];
        hours = currentAlarm->getHours();
        minutes = currentAlarm->getMins();
        temp = hours;
        currentAlarm->edit(currentTarget);
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
};
