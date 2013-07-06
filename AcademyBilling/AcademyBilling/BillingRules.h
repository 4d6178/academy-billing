#pragma once
#include "Subscriber.h"
#include "Call.h"

namespace AcademyBilling
{
    class Subscriber;

    class BillingRules
    {
    public:
        BillingRules(void);
        virtual ~BillingRules(void);
        //updates subscriber according to call, returns amount of money charged
        virtual int chargeForCall(Subscriber &subscriber, const Call &call) const =0;
    };
}
