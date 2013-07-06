#include "DefaultBillingRuleBlocks.h"

#include <regex>
#include <vector>
#include <string>

#include "Utility.h"
#include "Subscriber.h"
#include "DefaultBillingRules.h"

namespace AcademyBilling
{
    class DefaultBillingRules;

    bool isInsideNetwork(std::string number)
    {
        // Number should be in format +xx(xxx)xxxxxxx.
        std::string expression = ".*\\((050|066|095|099)\\).*";
        std::regex e(expression);
        return std::regex_match (number,e);
    }

    DefaultBillingRuleBlock::DefaultBillingRuleBlock(DefaultBillingRuleBlock* next) :
        next(next)
    {
    }

    int  DefaultBillingRuleBlock::invokeNext(Call &call, Subscriber &subscriber) const
    {
        if (next.get() != NULL)
            return next->chargeForCall(call, subscriber);
        return 0;
    }

    DefaultBillingRuleBlockConnectionFee::DefaultBillingRuleBlockConnectionFee(DefaultBillingRuleBlock* next) :
        DefaultBillingRuleBlock(next)
    {
    }

    int DefaultBillingRuleBlockConnectionFee::chargeForCall(Call &call, Subscriber &subscriber) const
    {
        subscriber.charge(fee);
        return fee + invokeNext(call, subscriber);
    }

     DefaultBillingRuleBlockWeekendFreeMinutes::DefaultBillingRuleBlockWeekendFreeMinutes(DefaultBillingRuleBlock* next) :
        DefaultBillingRuleBlock(next)
    {
    }

    int DefaultBillingRuleBlockWeekendFreeMinutes::chargeForCall(Call &call, Subscriber &subscriber) const
    {
        bool isWeekend = Utility::isWeekend(call.getTime());
        bool isInside = isInsideNetwork(call.getCalleeNumber());

        if (isWeekend && isInside) {
            int secondsCovered = Utility::secondsInMinute * minutesAmount;

            if (call.getDuration() <= secondsCovered)
                return 0;

            call.setDuration(call.getDuration() - secondsCovered);
        }
        return invokeNext(call, subscriber);
    }

     DefaultBillingRuleBlockFreeMinutesAfterCredit::DefaultBillingRuleBlockFreeMinutesAfterCredit(DefaultBillingRuleBlock* next) :
        DefaultBillingRuleBlock(next)
    {
    }

    int DefaultBillingRuleBlockFreeMinutesAfterCredit::chargeForCall(Call &call, Subscriber &subscriber) const
    {   
        DefaultBillingRules *tariff = static_cast<DefaultBillingRules *>(subscriber.getTariff());

        bool isInside = isInsideNetwork(call.getCalleeNumber());
        bool minutesNotExpired = (call.getTime() - tariff->lastCreditTime) >= minutesValidTime;
        if (isInside && minutesNotExpired) {
            int& freeMinutesSinceLastCredit = tariff->freeMinutesSinceLastCredit;
            int secondsCovered = freeMinutesSinceLastCredit * Utility::secondsInMinute;
            if (call.getDuration() <= secondsCovered) {
                // If call length was 1:01 take 2 minutes anyway.
                freeMinutesSinceLastCredit -= Utility::secondsToMinutesWithCeiling(call.getDuration());
                return 0;
            }
            call.setDuration(call.getDuration() - secondsCovered);
            freeMinutesSinceLastCredit = 0;
        }
        return invokeNext(call, subscriber);
    }

     DefaultBillingRuleBlockChargeFixedMinuteFee::DefaultBillingRuleBlockChargeFixedMinuteFee(DefaultBillingRuleBlock* next) :
        DefaultBillingRuleBlock(next)
    {
    }

    int DefaultBillingRuleBlockChargeFixedMinuteFee::chargeForCall(Call &call, Subscriber &subscriber) const
    {
        int fee;
        if(isInsideNetwork(call.getCalleeNumber()))
            fee = feeInside;
        else
            fee = feeOutside;

        int callDurationInMinutes = Utility::secondsToMinutesWithCeiling(call.getDuration());
        int cost = callDurationInMinutes * fee;
        subscriber.charge(cost);
        return cost + invokeNext(call, subscriber);
    }
}
