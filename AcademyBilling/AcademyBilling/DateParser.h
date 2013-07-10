#pragma once

#include <string>
#include <ctime>

namespace AcademyBilling
{
    class DateParser
    {
    public:
        DateParser(const std::string &date);
        const time_t parseDate() const;
    private:
        bool checkDateFormat(const std::string &date) const;
        bool checkDateLimits(const tm &timeInfo) const;

    private:
        std::string date;
    };
}
