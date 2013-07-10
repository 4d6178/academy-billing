#pragma once
#include <string>
#include <vector>
#include <json/json.h>

#include "SubscriberStorage.h"
#include "BillingRules.h"

namespace AcademyBilling
{
    class JsonSubscriberStorage : public SubscriberStorage
    {
    public:
        JsonSubscriberStorage(const std::string &jsonFilePath, BillingRules *rules);
        void addSubscriber(const Subscriber &subscriber);
        void getAllSubscribers(std::vector<Subscriber> &subscribers);
        Subscriber* findSubscriber(const std::string &number);
        ~JsonSubscriberStorage(void);

    private:
        void loadSubscribers();
        Refill getFirstRefill(size_t subscriberIndex) const; 

    private:
        Json::Value jsonSubscribersArray;
        std::vector<Subscriber> subscribers;
        BillingRules *rules;
    };
}

