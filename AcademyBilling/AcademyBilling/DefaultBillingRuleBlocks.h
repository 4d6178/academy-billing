#pragma once
#include <vector>
#include <string>

#include "BillingRules.h"
#include "Utility.h"

namespace AcademyBilling
{
    class DefaultBillingRules;
    
    /** 
    *   Rule block interface. 
    *   Each block may do some partial call cost calculation and then invoke next block.
    */
    class DefaultBillingRuleBlock
    {
        std::auto_ptr<DefaultBillingRuleBlock> next;
    public:
        int invokeNext(Call &call, Subscriber &subscriber) const;
        DefaultBillingRuleBlock(DefaultBillingRuleBlock* next);
        virtual int chargeForCall(Call &call, Subscriber &subscriber) const =0;
    };

    class DefaultBillingRuleBlockConnectionFee :
        public DefaultBillingRuleBlock
    {
        static const int fee = 33;
    public:
        DefaultBillingRuleBlockConnectionFee(DefaultBillingRuleBlock* next);
        int chargeForCall(Call &call, Subscriber &subscriber) const;
    };

    class DefaultBillingRuleBlockWeekendFreeMinutes :
        public DefaultBillingRuleBlock
    {
        static const int minutesAmount = 5;
    public:
        DefaultBillingRuleBlockWeekendFreeMinutes(DefaultBillingRuleBlock* next);
        int chargeForCall(Call &call, Subscriber &subscriber) const;
    };

    class DefaultBillingRuleBlockFreeMinutesAfterCredit :
        public DefaultBillingRuleBlock
    {
        static const int minutesValidTime = 30 * Utility::secondsInDay;
    public:
        DefaultBillingRuleBlockFreeMinutesAfterCredit(DefaultBillingRuleBlock* next);
        int chargeForCall(Call &call, Subscriber &subscriber) const;
    };

    class DefaultBillingRuleBlockChargeFixedMinuteFee :
        public DefaultBillingRuleBlock
    {
        static const int feeInside = 50;
        static const int feeOutside = 95;
    public:
        DefaultBillingRuleBlockChargeFixedMinuteFee(DefaultBillingRuleBlock* next);
        int chargeForCall(Call &call, Subscriber &subscriber) const;
    };
}
