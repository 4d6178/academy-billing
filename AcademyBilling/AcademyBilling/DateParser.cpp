#include <regex>
#include <stdexcept>
#include <sstream>

#include "DateParser.h"

namespace AcademyBilling
{
    const time_t DateParser::parseDate(const std::string &date)
    {
        if (!checkDateFormat(date)) {
            throw std::runtime_error("Date should be formatted as \"dd.mm.yyyy HH:mm:ss\"");
        }

        std::stringstream dateStream(date);
        tm timeInfo;
        char delimeter;
        dateStream >> timeInfo.tm_mday >> delimeter;
        dateStream >> timeInfo.tm_mon >> delimeter;
        dateStream >> timeInfo.tm_year >> delimeter;
        dateStream >> timeInfo.tm_hour >> delimeter;
        dateStream >> timeInfo.tm_min >> delimeter;
        dateStream >> timeInfo.tm_sec;

        timeInfo.tm_mon -= 1;
        timeInfo.tm_year -= 1900;
        checkDateLimits(timeInfo);

        return mktime(&timeInfo);
    }

    bool DateParser::checkDateFormat(const std::string &date)
    {
        std::regex dateRegex("\\d{2}\\.\\d{2}\\.\\d{4} \\d{2}:\\d{2}:\\d{2}");
        return std::regex_match(date, dateRegex);
    }

    bool DateParser::checkDateLimits(const tm &timeInfo)
    {
        bool daysOutOfRange = (timeInfo.tm_mday < 1 || timeInfo.tm_mday > 31);
        bool monthsOutOfRange = (timeInfo.tm_mon < 0 || timeInfo.tm_mon > 11);
        bool yearsOutOfRange = (timeInfo.tm_year < 0);
        bool hoursOutOfRange = (timeInfo.tm_hour < 0 || timeInfo.tm_hour > 23);
        bool minutesOutOfRange = (timeInfo.tm_min < 0 || timeInfo.tm_min > 59);
        bool secondsOutOfRange = (timeInfo.tm_sec < 0 || timeInfo.tm_sec > 59);

        if (daysOutOfRange || monthsOutOfRange || yearsOutOfRange
        || hoursOutOfRange || minutesOutOfRange || secondsOutOfRange) {
            throw std::out_of_range("Date is out of range");
        }

        return true;
    }
}