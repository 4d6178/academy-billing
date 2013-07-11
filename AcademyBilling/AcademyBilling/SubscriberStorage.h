#pragma once
#include <vector>

#include "Subscriber.h"

namespace AcademyBilling
{
    //interface for any kind of subscriber storage
    class SubscriberStorage
    {
    public:
        virtual void addSubscriber(const Subscriber &subscriber) = 0;
        virtual const std::vector<Subscriber>& getAllSubscribers() const = 0;
        virtual Subscriber* findSubscriber(const std::string &number) = 0;
    };
}
