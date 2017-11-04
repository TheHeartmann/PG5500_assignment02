#pragma once

#include <Arduino.h>
#include <Keypad.h>
#include <ctype.h>
#include "AlarmDisplay.h"
#include <RTClib.h>

#define ROWS 4
#define COLS 4

enum TimeDivision
{
    Hour,
    Minutes
};

class InputHandler
{
  public:
    InputHandler(AlarmDisplay *(*alarms)[4]) : alarms(alarms) {}
    void readInput()
    {
        auto key = keypad.getKey();

        if (!key)
            return;

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
                handleNumeral(key);
            }
            leader = noInput;
        }
    }

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
            if (isModifier)
            {
                editingAlarm == false;
                if (key == set)
                {
                    currentAlarm->save();
                }
                else if (key == turnOff)
                {
                    currentAlarm->cancel();
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
                alarmHandler.changeTarget((TimeDivision)(1 - target));
            }
        }
    }

    // variables
    char keys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};

    byte rowPins[ROWS] = {5, 4, 3, 2};
    byte colPins[COLS] = {A0, A1, A2, A3};

    Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

    AlarmDisplay *(*alarms)[4];
    AlarmDisplay *currentAlarm;
    const char set = '#';
    const char turnOff = '*';
    const char noInput = ' ';

    char leader = noInput;
    bool editingAlarm = false;

    class AlarmHandler
    {
      public:
        char leader;
        AlarmDisplay *alarm;
        String hours;
        String minutes;
        String temp;
        TimeDivision currentTarget;

        void changeTarget(TimeDivision newTarget)
        {
            // currentTarget = (TimeDivision)(1 - currentTarget);
            currentTarget = newTarget;
            temp = "";
        }

        void registerNumeral(const char num)
        {
            temp += String(num);

            alarm->display(hours, minutes);

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
        void toggle()
        {
            alarm->toggle();
        }
    };

    AlarmHandler alarmHandler;
};
