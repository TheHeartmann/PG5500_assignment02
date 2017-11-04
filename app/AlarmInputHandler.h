#pragma once

#include <Arduino.h>
#include <Keypad.h>
#include <ctype.h>
#include "AlarmDisplay.h"
#include <RTClib.h>
#include "AlarmInputHandler.h"

enum TimeDivision
{
    Hour,
    Minutes
};

class AlarmInputHandler
{
  public:
    // AlarmInputHandler(AlarmDisplay *(*alarms)[4]) : alarms(alarms) {}
    void setAlarmsArray(AlarmDisplay *(*alarmArray)[4])
    {
        alarms = alarmArray;
    }
    void handleInput(char key)
    {
        if (leader == noInput)
        {
            handleNoLeader(key);
        }
        else
        {
            if (isModifier(key))
            {
                handleModified(key);
            }
            else if (isDigit(key) && editingAlarm)
            {
                registerNumeral(key);
            }
            leader = noInput;
        }
    }

    void changeTarget(TimeDivision newTarget)
    {
        // currentTarget = (TimeDivision)(1 - currentTarget);
        currentTarget = newTarget;
        temp = "";
    }

    void registerNumeral(const char num)
    {
        temp += String(num);

        currentAlarm->display(hours, minutes);

        if (temp.length() != 2)
            return;

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
    void reset();

  private:
    bool isModifier(char c) { return c == set || c == turnOff; }
    void handleNoLeader(char key)
    {
        if (isAlpha(key))
        {
            (*alarms)[key - 'A']->toggle();
        }
        else if (key == set || key == turnOff)
        {
            leader = key;
        }
    }

    void handleModified(char key)
    {
        if (leader == set)
        {
            if (isModifier(key))
            {
                editingAlarm == false;
                if (key == set)
                {
                    // currentAlarm->save();
                }
                else if (key == turnOff)
                {
                    // currentAlarm->cancel();
                }
            }
            else if (isAlpha(key))
            {
                currentAlarm = (*alarms)[key - 'A'];
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
                changeTarget((TimeDivision)(1 - currentTarget));
            }
        }
    }

    String hours;
    String minutes;
    String temp;
    TimeDivision currentTarget;

    AlarmDisplay *(*alarms)[4];
    AlarmDisplay *currentAlarm;
    const char set = '#';
    const char turnOff = '*';
    const char noInput = ' ';

    char leader = noInput;
    bool editingAlarm = false;
};
