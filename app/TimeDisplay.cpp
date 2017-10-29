#include "TimeDisplay.h"

TimeDisplay::TimeDisplay(TFT &tft, RTC_DS1307 &rtc, const short textSize, const Vector hourPos)
    : tft(&tft), rtc(rtc), SIZE(textSize), HOUR_POS(hourPos), MIN_POS({hourPos.x + 3 * textSize * 6, hourPos.y})
{
    const TextOptions HOUR_OPTS = TextOptions{HOUR_POS, SIZE, 3};
    const TextOptions MIN_OPTS = TextOptions{MIN_POS, SIZE, 3};
    const TextOptions SEP_OPTS = TextOptions{{HOUR_POS.x + SIZE * 6 * 2, HOUR_POS.y}, SIZE, 2};

    hour = TextSection(tft, HOUR_OPTS, HH);
    minutes = TextSection(tft, MIN_OPTS, MM);
    // auto separator = TextSection(tft, SEP_OPTS, SEPARATOR);
    // const auto sep = String(":");
    // separator.update(&sep);

    // writeSeparator();
}

String TimeDisplay::pad(int number) const
{
    auto numberString = String(number);
    return numberString.length() < 2 ? "0" + numberString : numberString;
}

void TimeDisplay::writeSeparator() const
{
    tft->stroke(255, 255, 255);
    tft->setTextSize(SIZE);
    tft->text(SEPARATOR, HOUR_POS.x + SIZE * 6 * 2, HOUR_POS.y);
}