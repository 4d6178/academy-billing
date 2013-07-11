#pragma once
#include <string>
#include <vector>
#include <json/json.h>

#include "SubscriberStorage.h"
#include "BillingRulesProvider.h"

namespace AcademyBilling
{
    class JsonSubscriberStorage : public SubscriberStorage
    {
    public:
        JsonSubscriberStorage(const std::string &jsonFilePath, BillingRulesProvider &provider);
        void addSubscriber(const Subscriber &subscriber);
        const std::vector<Subscriber>& getAllSubscribers() const;
        Subscriber* findSubscriber(const std::string &number);
        ~JsonSubscriberStorage(void);

    private:
        void loadSubscribers();
        Refill getFirstRefill(size_t subscriberIndex) const; 

    private:
        Json::Value jsonSubscribersArray;
        std::vector<Subscriber> subscribers;
        BillingRulesProvider *rulesProvider;
    };
}

