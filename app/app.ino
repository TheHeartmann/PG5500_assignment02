#include <TFT.h> // Arduino LCD library
#include <SPI.h>
#include <Keypad.h>
#include <ctype.h>
#include <RTClib.h>
#include <SimpleTimer.h>

#include "Vector.h"
#include "RGB.h"
#include "TextOptions.h"
#include "TextSection.h"
#include "TimeKeeper.h"

// RTC
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

// Keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {5, 4, 3, 2};     //connect to the row pinouts of the keypad
byte colPins[COLS] = {A0, A1, A2, A3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String (*testString)(char end);

// TFT
// pin definition for the Uno
#define cs 10
#define dc 9
#define rst 8

// create an instance of the library
TFT tft = TFT(cs, dc, rst);
SimpleTimer timer;
auto tk = TimeKeeper(tft, rtc);

void setup()
{
    // init RTC
    if (!rtc.begin()) { while (1) ; }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    tft.begin();
    tft.background(0, 0, 0);
    tk.writeSeparator();
    updateTk();

    timer.setInterval(1000, updateTk);
    // test = &multiply;
    // testString = &my_append;
}

void updateTk() {
    tk.updateTime();
}

int multiply(int a, int b)
{
    return a * b;
}

String my_append(char c)
{
    return "I: " + c;
}

void loop()
{
    timer.run();

    // char key = keypad.getKey();

    // if (key)
    // {
    //     Serial.println(key);
    //     testString(key).toCharArray(HHMM, 4);
    //     // HHMM[0] = key;
    //     // if (isdigit(key)) test =
    // }
    // else
    // {
    //     //   test(3, 5).toCharArray()
    //     //   test
    // }
}