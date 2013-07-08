#pragma once
#include "Subscriber.h"
#include "Call.h"

namespace AcademyBilling
{
    class Subscriber;
    class Call;

    class BillingRules
    {
    public:
        BillingRules(void);
        virtual ~BillingRules(void);
        //updates subscriber according to call, returns amount of money charged
        virtual int chargeForCall(const Call &call, Subscriber &subscriber) =0;
    };
}
