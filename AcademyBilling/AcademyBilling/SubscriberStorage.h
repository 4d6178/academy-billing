#pragma once
#include <vector>

#include "Subscriber.h"

namespace AcademyBilling
{
    //interface for any kind of subscriber storage
    class SubscriberStorage
    {
    public:
        virtual ~SubscriberStorage(void);
        virtual void addSubscriber(const Subscriber &subscriber) = 0;
        virtual void getAllSubscribers(std::vector<Subscriber> &subscribers) = 0;
        virtual Subscriber* findSubscriber(const std::string &number) = 0;
    };
}
