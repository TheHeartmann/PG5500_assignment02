#include "TimeKeeper.h"

TimeKeeper::TimeKeeper(TFT &tft, RTC_DS1307 &rtc)
    : TimeDisplay(tft, rtc, 4, Vector{0, 20})
{
    // text coordinates
    const Vector DATE_POS = {0, RESOLUTION.y - DATE_SIZE * 10};
    const Vector SECONDS_POS = {HOUR_POS.x + 5 * HOUR_SIZE * 6 + 5, HOUR_POS.y + 15};

    const TextOptions DATE_OPTS = TextOptions{DATE_POS, DATE_SIZE, 15};
    const TextOptions SEC_OPTS = TextOptions{SECONDS_POS, SECOND_SIZE, 3};

    // text section objects
    date = TextSection(tft, DATE_OPTS, DATE);
    seconds = TextSection(tft, SEC_OPTS, SECS);
}

void TimeKeeper::update() const
{
    static int prevDate, prevHour, prevMin;
    auto now = rtc.now();
    auto currentDate = now.day();
    auto currentHour = now.hour();
    auto currentMinute = now.minute();

    auto ss = pad(now.second());
    seconds.update(ss);

    if (currentMinute != prevMin)
    {
        auto ms = pad(currentMinute);
        minutes.update(ms);
        if (currentHour != prevHour)
        {
            auto hs = pad(currentHour);
            hour.update(hs);
            if (currentDate != prevDate)
            {
                auto ds = getDateString(now);
                date.update(ds);
            }
        }
    }

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