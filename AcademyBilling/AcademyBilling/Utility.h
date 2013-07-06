#pragma once
#include <ctime>

namespace AcademyBilling
{
    namespace Utility
    {
        const int secondsInMinute = 60;
        const int secondsInHour = 60 * secondsInMinute;
        const int secondsInDay = 24 * secondsInHour;

        bool isWeekend(time_t time);
        int secondsToMinutesWithCeiling(int seconds);
    }
}
