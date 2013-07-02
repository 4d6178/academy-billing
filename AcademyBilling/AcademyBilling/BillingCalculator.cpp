#include "BillingCalculator.h"

namespace AcademyBilling
{
    BillingCalculator::BillingCalculator(void)
    {
    }

    BillingCalculator::~BillingCalculator(void)
    {
    }

    void BillingCalculator::setSubscrberStorage(std::shared_ptr<SubscriberStorage> subscriberStorage) const
    {
    }

    void BillingCalculator::chargeForSingleCall(const Call& call)
    {
    }

    void BillingCalculator::chargeForMultipleCalls(std::vector<Call>& call)
    {
    }
}
