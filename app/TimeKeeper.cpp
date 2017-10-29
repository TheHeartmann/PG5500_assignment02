#include "TimeKeeper.h"

void TimeKeeper::updateTime()
{
    static int prevDate, prevHour, prevMin;
    auto now = rtc.now();
    auto currentDate = now.day();
    auto currentHour = now.hour();
    auto currentMinute = now.minute();

    auto ds = getDateString(now);
    auto hs = pad(currentHour);
    auto ms = pad(currentMinute);
    auto ss = pad(now.second());

    if (currentDate != prevDate) date.update(&ds);
    // if (currentDate != prevDate) date.update(&getDateString(&now));
    if (currentHour != prevHour) hour.update(&hs);
    // if (currentHour != prevHour) hour.update(&pad(currentHour));
    if (currentMinute != prevMin) minutes.update(&ms);
    // if (currentMinute != prevMin) minutes.update(&pad(currentMinute));
    seconds.update(&ss);
    // seconds.update(&pad(now.second()));

    prevDate = currentDate;
    prevHour = currentHour;
    prevMin = currentMinute;
}

String TimeKeeper::getDateString(const DateTime &now) const
{
    auto dotw = daysOfTheWeek[now.dayOfTheWeek()];
    auto year = String(now.year());
    auto month = pad(now.month());
    auto day = pad(now.day());
    return String(year + "/" + month + "/" + day + " " + dotw);
}

void TimeKeeper::writeSeparator() const
{
    tft.stroke(255, 255, 255);
    tft.setTextSize(HOUR_SIZE);
    tft.text(SEPARATOR, HOUR_POS.x + HOUR_SIZE * 6 * 2, HOUR_Y);
}

String TimeKeeper::pad(int number) const
{
    auto numberString = String(number);
    return numberString.length() < 2 ? "0" + numberString : numberString;
}
