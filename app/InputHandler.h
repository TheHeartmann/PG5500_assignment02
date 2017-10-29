#pragma once

#include <Arduino.h>
#include <Keypad.h>
#include <ctype.h>
#include "Alarm.h"
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
    InputHandler(const Alarm *alarms) : alarms(alarms) {}
    void readInput();

  private:
    void registerNumeral(const char num) const;
    // Keypad
    char keys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};

    byte rowPins[ROWS] = {5, 4, 3, 2};     //connect to the row pinouts of the keypad
    byte colPins[COLS] = {A0, A1, A2, A3}; //connect to the column pinouts of the keypad
    Alarm *alarms;
    Alarm *currentAlarm;
    const char letters[3] = {'A', 'B', 'C'};
    const char chord = '#';
    const char turnOff = '*';
    const char noInput = ' ';
    const char escape = 'D';

    Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
};

class InputParser {
public:
  char leader;
  Alarm *alarm;
  DateTime t;
  int hours;
  int minutes;

  void registerNumeral(const char num, const TimeDivision target);
  void reset();
};

void InputHandler::readInput()
{
    static char leader = noInput;
    static bool editingAlarm = false;
    static TimeDivision target = TimeDivision::Hour;
    auto key = keypad.getKey();

    if (!key)
        return;

    if (key == turnOff || key == chord)
    {
        leader = key;
        editingAlarm = false;
    }

    if (leader == noInput)
        return;

    if (isAlpha(key))
        currentAlarm = &alarms[key];
    else if (isDigit(key))
    {
        registerNumeral(key, target);
    }
}

void InputParser::registerNumeral(const char num, const TimeDivision target) {
    static DateTime newTime;
    static String parsedValue = "";
    parsedValue += String(num);

    if (parsedValue.length() != 2)
        return;

    int value = parsedValue.toInt();
    int hours, mins;

    if (target == TimeDivision::Hour) {
        hours = value;
        mins = newTime.minute();
    } else {
        hours = newTime.hour();
        mins = value;
    }

    newTime = DateTime.makeTime(0, mins, hours, 0, 0, 0);
}