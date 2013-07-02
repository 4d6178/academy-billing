#pragma once
#include "Subscriber.h"
#include "Call.h"
#include "SubscriberStorage.h"
#include<vector>

namespace AcademyBilling
{
    class BillingCalculator
    {
    private:
        std::shared_ptr<SubscriberStorage> subscriberStorage;
    public:
        BillingCalculator(void);
        ~BillingCalculator(void);
        void setSubscrberStorage(std::shared_ptr<SubscriberStorage> subscriberStorage) const;
        //warning:call must be made after any other call, that has been already processed
        void chargeForSingleCall(const Call& call);
        //warning:all calls must be made after any other call, that has been already processed
        void chargeForMultipleCalls(std::vector<Call>& call);
    };
}
