#include "Utility.h"

namespace AcademyBilling
{
    namespace Utility
    {
        bool isWeekend(time_t time)
        {
            tm timeInfo;
            localtime_s(&timeInfo, &time);
            int weekDay=timeInfo.tm_wday;
            bool isWeekend = (weekDay == 0) || (weekDay == 6);
            return isWeekend;
        }

        int secondsToMinutesWithCeiling(int seconds)
        {
            return (seconds + secondsInMinute - 1)/secondsInMinute;
        }
    }
}
