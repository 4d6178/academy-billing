#pragma once
#include"Subscriber.h"
#include<vector>

namespace AcademyBilling
{
    //interface for any kind of subscriber storage
    class SubscriberStorage
    {
    public:
        virtual ~SubscriberStorage(void);
        virtual void addSubscriber(const Subscriber &subscriber);
        virtual void getAllSubscribers(std::vector<Subscriber> &subscriber);
        virtual Subscriber* findSubscriber(std::string number);
    };
}
