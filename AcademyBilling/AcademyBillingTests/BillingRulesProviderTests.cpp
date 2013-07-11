#include <BillingRulesProvider.h>
#include <DefaultBillingRules.h>

#include "BillingRulesProviderTests.h"

namespace AcademyBillingTesting
{
    TEST(BillingRulesProviderTests, testGeneral)
    {
        AcademyBilling::BillingRulesProvider provider;
        EXPECT_THROW(provider.getRules("someRules"), std::runtime_error);
        provider.addRules("someRules", &AcademyBilling::DefaultBillingRules());
        EXPECT_NO_THROW(provider.getRules("someRules"));
        EXPECT_THROW(provider.addRules("someRules", &AcademyBilling::DefaultBillingRules()), std::runtime_error);
    }
}