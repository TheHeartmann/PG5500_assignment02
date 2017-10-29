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
char DATE[15];
char HH[3];
char MM[3];
// char PREV_SECS[3];
char SECS[3];
const char SEPARATOR[2] = ":";

// text sizes
const short DATE_SIZE = 1;
const short HOUR_SIZE = 4;
const short SECOND_SIZE = 2;

const Vector RESOLUTION = {tft.width(), tft.height()};

// text width appears to be 60% of the height

// text coordinates
const Vector DATE_POS = {0, RESOLUTION.y - DATE_SIZE * 10};
const short HOUR_Y = 20;
const Vector HOUR_POS = {0, HOUR_Y};
const Vector MINUTES_POS = {HOUR_POS.x + 3 * HOUR_SIZE * 6, HOUR_Y};
const Vector SECONDS_POS = {HOUR_POS.x + 5 * HOUR_SIZE * 6 + 5, HOUR_Y + 15};

const auto DATE_OPTS = TextOptions{DATE_POS, DATE_SIZE, 15};
const auto HOUR_OPTS = TextOptions{HOUR_POS, HOUR_SIZE, 3};
const auto MIN_OPTS = TextOptions{MINUTES_POS, HOUR_SIZE, 3};
const auto SEC_OPTS = TextOptions{SECONDS_POS, SECOND_SIZE, 3};
auto date = TextSection(tft, DATE_OPTS, DATE);
auto hour = TextSection(tft, HOUR_OPTS, HH);
auto minutes = TextSection(tft, MIN_OPTS, MM);
auto seconds = TextSection(tft, SEC_OPTS, SECS);

SimpleTimer timer;

void setup()
{
    // init RTC
    if (!rtc.begin()) { while (1) ; }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

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

void updateTime()
{
    static int prevDate, prevHour, prevMin;
    auto now = rtc.now();
    auto currentDate = now.day();
    auto currentHour = now.hour();
    auto currentMinute = now.minute();

    if (currentDate != prevDate) date.update(&getDate(&now));
    if (currentHour != prevHour) hour.update(&pad(currentHour));
    if (currentMinute != prevMin) minutes.update(&pad(currentMinute));
    seconds.update(&pad(now.second()));

    prevDate = currentDate;
    prevHour = currentHour;
    prevMin = currentMinute;
}

String getDate(const DateTime *now)
{
    auto dotw = daysOfTheWeek[now->dayOfTheWeek()];
    auto year = String(now->year());
    auto month = pad(now->month());
    auto day = pad(now->day());

    return String(year + "/" + month + "/" + day + " " + dotw);
}

void writeText(const DateTime *now, char *prevText, const char *newText, const TextOptions *DATE_OPTS) {
    write(prevText, newText, DATE_OPTS);
    memcpy(prevText, newText, DATE_OPTS->length);
}

void writeDate(const DateTime *now)
{
    static char prevDate[15];
    auto dateString = getDate(now);
    dateString.toCharArray(DATE, 15);
    write(prevDate, DATE, &DATE_OPTS);
    memcpy(prevDate, DATE, 15 * sizeof(char));
}

void writeHH(const DateTime *now)
{
    static char prevTime[3];
    auto hour = pad(now->hour());
    hour.toCharArray(HH, 3);
    write(prevTime, HH, &HOUR_OPTS);
    memcpy(prevTime, HH, 3 * sizeof(char));
}

void writeMM(const DateTime *now)
{
    static char prevTime[3];
    auto minutes = pad(now->minute());
    minutes.toCharArray(MM, 3);
    write(prevTime, MM, &MIN_OPTS);
    memcpy(prevTime, MM, 3 * sizeof(char));
}

void writeSS(const DateTime *now)
{

    // auto text = pad(now->second());
    // text.toCharArray(SECS, 3);
    // seconds.write(SECS);

    seconds.update(&pad(now->second()));

    // static char prevSecs[3];
    // auto seconds = pad(now->second());
    // seconds.toCharArray(SECS, 3);
    // write(prevSecs, SECS, &SEC_OPTS);
    // memcpy(prevSecs, SECS, 3 * sizeof(char));
}

void writeSeparator()
{
    tft.stroke(255, 255, 255);
    tft.setTextSize(HOUR_SIZE);
    tft.text(SEPARATOR, HOUR_POS.x + HOUR_SIZE * 6 * 2, HOUR_Y);
}

void write(const char *prevText, const char *newText, const TextOptions *DATE_OPTS)
{
    tft.setTextSize(DATE_OPTS->size);
    draw(prevText, DATE_OPTS->pos, BLACK);
    draw(newText, DATE_OPTS->pos, WHITE);
}

void draw(const char *text, const Vector position, RGB color)
{
    tft.stroke(color.r, color.g, color.b);
    tft.text(text, position.x, position.y);
}

String pad(int number)
{
    auto numberString = String(number);
    return numberString.length() < 2 ? "0" + numberString : numberString;
}