#include "BillingCalculator.h"

#include <exception>
#include <assert.h>

#include "BillingRules.h"

namespace AcademyBilling
{
    BillingCalculator::BillingCalculator(void)
    {
    }

    BillingCalculator::~BillingCalculator(void)
    {
    }

    void BillingCalculator::setSubscrberStorage(std::shared_ptr<SubscriberStorage> subscriberStorage)
    {
        this->subscriberStorage = subscriberStorage;
    }

    void BillingCalculator::chargeForSingleCall(const Call& call)
    {
        assert(subscriberStorage.get() == NULL && "Subscriber storage not set");
        Subscriber * subscriber = subscriberStorage->findSubscriber(call.getCallerNumber());
        if(subscriber == NULL)
            throw std::logic_error("Call from unknown subscriber.");
        BillingRules * billingRules = subscriber->getTariff();
        assert(billingRules != NULL && "Tarif not defined for subscriber");
        billingRules->chargeForCall(call, *subscriber);
    }

    void BillingCalculator::chargeForMultipleCalls(const std::vector<Call>& calls)
    {
        for (auto call = calls.begin(); call != calls.end(); ++call)
            chargeForSingleCall(*call);
    }
}
