#include <TFT.h> // Arduino LCD library
#include <SPI.h>
#include <Keypad.h>
#include <ctype.h>
#include <RTClib.h>
#include <SimpleTimer.h>

#include "vector.h"
#include "rgb.h"

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

// char array to print to the screen
char date[15];
char HH[3];
char MM[3];
char secs[3];
const char SEPARATOR[2] = ":";

// text sizes
const int DATE_SIZE = 1;
const int HOUR_SIZE = 4;
const int SECOND_SIZE = 2;

const Vector RESOLUTION = {tft.width(), tft.height()};

// text width appears to be 60% of the height

// text coordinates
const Vector DATE_POS = {0, RESOLUTION.y - DATE_SIZE * 10};
const short HOUR_Y = 20;
const Vector HOUR_POS = {0, HOUR_Y};
const Vector MINUTES_POS = {HOUR_POS.x + 3 * HOUR_SIZE * 6, HOUR_Y};
const Vector SECONDS_POS = {HOUR_POS.x + 5 * HOUR_SIZE * 6 + 5, HOUR_Y + 15};

SimpleTimer timer;

void setup()
{
    // init RTC
    if (!rtc.begin())
    {
        while (1)
            ;
    }

    if (!rtc.isrunning())
    {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    tft.begin();
    tft.background(0, 0, 0);
    writeSeparator();

    updateTime();
    timer.setInterval(1000, updateTime);
    // test = &multiply;
    // testString = &my_append;
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
    // DateTime now = rtc.now();
    // writeHHMM(&now);
    // writeSS(&now);
    // writeDate(&now);

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
    // set the font color
    // write(HHMM, HHMM, {})
    // tft.stroke(255, 255, 255);
    // // print the sensor value
    // // tft.text(HHMM, 0, 20);
    // tft.setTextSize(SECOND_SIZE);
    // tft.text(secs, 125, 35);
    // // tft.setTextSize(HOUR_SIZE);

    // // wait for a moment
    // delay(250);
    // // erase the text you just wrote
    // tft.stroke(0, 0, 0);
    // // tft.text(HHMM, 0, 20);

    // tft.setTextSize(SECOND_SIZE);
    // tft.text(secs, 125, 35);
    // // tft.setTextSize(HOUR_SIZE);
}

void updateTime()
{
    static int prevDate, prevHour, prevMin;
    auto now = rtc.now();
    auto date = now.day();
    auto hour = now.hour();
    auto minutes = now.minute();
    auto seconds = now.second();

    if (date != prevDate) writeDate(&now);
    if (hour != prevHour) writeHH(&now);
    if (minutes != prevMin) writeMM(&now);
    writeSS(&now);

    prevDate = date;
    prevHour = hour;
    prevMin = minutes;
}

String getDate(DateTime *now)
{
    auto dotw = daysOfTheWeek[now->dayOfTheWeek()];
    auto year = String(now->year());
    auto month = pad(now->month());
    auto day = pad(now->day());

    return String(year + "/" + month + "/" + day + " " + dotw);
}

void writeDate(DateTime *now)
{
    static char prevDate[15];
    auto dateString = getDate(now);
    dateString.toCharArray(date, 15);
    write(prevDate, date, DATE_POS, DATE_SIZE);
}

void writeHH(DateTime *now)
{
    static char prevTime[3];
    auto hour = pad(now->hour());
    hour.toCharArray(HH, 3);
    write(prevTime, HH, HOUR_POS, HOUR_SIZE);
    memcpy(prevTime, HH, 3 * sizeof(char));
}

void writeMM(DateTime *now)
{
    static char prevTime[3];
    auto minutes = pad(now->minute());
    minutes.toCharArray(MM, 3);
    write(prevTime, MM, MINUTES_POS, HOUR_SIZE);
    memcpy(prevTime, MM, 3 * sizeof(char));
}

void writeSS(DateTime *now)
{
    static char prevSecs[3];
    auto seconds = pad(now->second());
    seconds.toCharArray(secs, 3);
    write(prevSecs, secs, {125, 35}, SECOND_SIZE);
    memcpy(prevSecs, secs, 3 * sizeof(char));
}

void writeSeparator()
{
    tft.stroke(255, 255, 255);
    tft.setTextSize(HOUR_SIZE);
    tft.text(SEPARATOR, HOUR_POS.x + HOUR_SIZE * 6 * 2, HOUR_Y);
}

void write(char *prevText, char *newText, Vector position, int textSize)
{
    tft.setTextSize(textSize);
    draw(prevText, position, BLACK);
    draw(newText, position, WHITE);
}

void draw(char *text, Vector position, RGB color)
{
    tft.stroke(color.r, color.g, color.b);
    tft.text(text, position.x, position.y);
}

String pad(int number)
{
    auto numberString = String(number);
    return numberString.length() < 2 ? "0" + numberString : numberString;
}