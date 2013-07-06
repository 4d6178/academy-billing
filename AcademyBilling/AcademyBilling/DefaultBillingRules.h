#pragma once
#include <memory>

#include "BillingRules.h"
#include "DefaultBillingRuleBlocks.h"

namespace AcademyBilling
{
    class DefaultBillingRulesRuleset;

    class DefaultBillingRules :
        public BillingRules
    {
        friend DefaultBillingRuleBlockFreeMinutesAfterCredit;
        int freeMinutesSinceLastCredit;
        time_t lastCreditTime;
        static DefaultBillingRulesRuleset defaultBillingRulesRuleset;

    public:
        DefaultBillingRules(void);
        ~DefaultBillingRules(void);
        int chargeForCall(const Call &call, Subscriber &subscriber);
    };

    class DefaultBillingRulesRuleset
    {
        std::auto_ptr<DefaultBillingRuleBlock> firstRuleBlock;
    public:
        int chargeForCall(Call call, Subscriber &subscriber);
        DefaultBillingRulesRuleset();
    };
}
