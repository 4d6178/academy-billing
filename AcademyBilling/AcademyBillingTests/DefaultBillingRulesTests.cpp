#include "DefaultBillingRulesTests.h"

#include <DefaultBillingRules.h>

namespace AcademyBillingTesting
{
    TEST_F(DefaultBillingRulesTests, test_ok)
    {
        ASSERT_TRUE(true);
    }

    TEST_F(DefaultBillingRulesTests, test_fail)
    {
        ASSERT_NO_THROW(throw 1);
    }
}