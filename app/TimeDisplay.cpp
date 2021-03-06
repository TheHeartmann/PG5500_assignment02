#include "TimeDisplay.h"

TimeDisplay::TimeDisplay(TFT &tft, RTC_DS1307 &rtc, const short textSize, const Vector hourPos, char separatorChar)
    : tft(&tft), rtc(rtc), SIZE(textSize), HOUR_POS(hourPos), MIN_POS({hourPos.x + 3 * textSize * 6, hourPos.y}), SEP_POS({HOUR_POS.x + SIZE * 6 * 2, HOUR_POS.y}), SEP(separatorChar)
{
    const TextOptions HOUR_OPTS = TextOptions{HOUR_POS, SIZE, 3};
    const TextOptions MIN_OPTS = TextOptions{MIN_POS, SIZE, 3};
    const TextOptions SEP_OPTS = TextOptions{SEP_POS, SIZE, 2};

    hour = TextSection(tft, HOUR_OPTS, HH);
    minutes = TextSection(tft, MIN_OPTS, MM);
    separator = TextSection(tft, SEP_OPTS, SEPARATOR);
}

void TimeDisplay::init() const
{
    const auto sep = String(SEP);
    separator.update(sep);
}

String TimeDisplay::pad(int number) const
{
    const auto numberString = String(number);
    return numberString.length() < 2 ? "0" + numberString : numberString;
}