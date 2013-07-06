#include "DefaultBillingRules.h"

#include "Subscriber.h"
#include "Utility.h"

namespace AcademyBilling
{
    DefaultBillingRules::DefaultBillingRules(void)
        :freeMinutesSinceLastCredit(30)
    {
    }

    DefaultBillingRules::~DefaultBillingRules(void)
    {
    }

    int DefaultBillingRules::chargeForCall(const Call &call, Subscriber &subscriber)
    {
        return defaultBillingRulesRuleset.chargeForCall(call, subscriber);
    }

    int DefaultBillingRulesRuleset::chargeForCall(Call call, Subscriber &subscriber)
    {
        return firstRuleBlock->chargeForCall(call,subscriber);
    }

    DefaultBillingRulesRuleset::DefaultBillingRulesRuleset()
    {
        firstRuleBlock =  std::auto_ptr<DefaultBillingRuleBlock>(
                            new DefaultBillingRuleBlockConnectionFee(
                            new DefaultBillingRuleBlockWeekendFreeMinutes(
                            new DefaultBillingRuleBlockFreeMinutesAfterCredit(
                            new DefaultBillingRuleBlockChargeFixedMinuteFee(NULL)))));
    }
}
