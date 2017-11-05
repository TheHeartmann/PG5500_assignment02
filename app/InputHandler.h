#pragma once

#include <Arduino.h>
#include <Keypad.h>
#include "AlarmDisplay.h"
#include <RTClib.h>
#include "AlarmInputHandler.h"

#define ROWS 4
#define COLS 4

class InputHandler
{
  public:
    InputHandler(AlarmDisplay *(*alarms)[4]) {
        alarmHandler.setAlarmsArray(alarms);
    }
    void readInput()
    {
        auto key = keypad.getKey();

        if (!key)
            return;

        alarmHandler.handleInput(key);
    }

  private:
    // variables
    char keys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};

    byte rowPins[ROWS] = {5, 4, 3, 2};
    byte colPins[COLS] = {A0, A1, A2, A3};

    Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
    AlarmInputHandler alarmHandler;
};
