#pragma once
#include "gtest\gtest.h"

namespace AcademyBillingTesting
{
    class DefaultBillingRulesTests :
        public testing::Test
    {
    protected:
        // Days of week should be from 0 to 6, where 0 is Sunday.
        time_t timeByDayOfWeek(int weekDay);
    };
}
