#pragma once
#include "billingrules.h"

namespace AcademyBilling
{
    class DefaultBillingRules :
        public BillingRules
    {
    public:
        DefaultBillingRules(void);
        ~DefaultBillingRules(void);
        int chargeForCall(Subscriber &subscriber, const Call &call) const;
    };
}
