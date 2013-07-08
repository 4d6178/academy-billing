#pragma once
#include<vector>
#include <memory>

#include "Subscriber.h"
#include "Call.h"
#include "SubscriberStorage.h"

namespace AcademyBilling
{
    class SubscriberStorage;
    class Call;

    class BillingCalculator
    {
    private:
        std::shared_ptr<SubscriberStorage> subscriberStorage;
    public:
        BillingCalculator(void);
        ~BillingCalculator(void);
        void setSubscrberStorage(std::shared_ptr<SubscriberStorage> subscriberStorage);
        //warning:call must be made after any other call, that has been already processed
        void chargeForSingleCall(const Call& call);
        //warning:all calls must be made after any other call, that has been already processed
        void chargeForMultipleCalls(const std::vector<Call>& calls);
    };
}
