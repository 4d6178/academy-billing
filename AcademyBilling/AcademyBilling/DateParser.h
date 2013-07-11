#pragma once

#include <string>
#include <ctime>

namespace AcademyBilling
{
    class DateParser
    {
    public:
        static const time_t parseDate(const std::string &date);
    private:
        static bool checkDateFormat(const std::string &date);
        static bool checkDateLimits(const tm &timeInfo);
    };
}
