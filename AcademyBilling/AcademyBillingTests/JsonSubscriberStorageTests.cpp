#include "JsonSubscriberStorageTests.h"

#include <JsonSubscriberStorage.h>
#include <DefaultBillingRules.h>

namespace AcademyBillingTesting
{
    TEST(JsonSubscriberStorageTests, testCreation)
    {
        AcademyBilling::BillingRulesProvider provider;
        provider.addRules("Default", &AcademyBilling::DefaultBillingRules());

        EXPECT_THROW(AcademyBilling::JsonSubscriberStorage storage("JsonTestFiles/FileNotExists.json", provider), std::runtime_error);
        EXPECT_THROW(AcademyBilling::JsonSubscriberStorage storage("JsonTestFiles/BadFormatted.json", provider), std::runtime_error);
        EXPECT_THROW(AcademyBilling::JsonSubscriberStorage storage("JsonTestFiles/MissingFields.json", provider), std::runtime_error);
        EXPECT_THROW(AcademyBilling::JsonSubscriberStorage storage("JsonTestFiles/MissingArray.json", provider), std::runtime_error);
        EXPECT_NO_THROW(AcademyBilling::JsonSubscriberStorage storage("JsonTestFiles/Subscribers.json", provider));
    }

    TEST(JsonSubscriberStorageTests, testGetAllSubscribers)
    {
        AcademyBilling::BillingRulesProvider provider;
        provider.addRules("Default", &AcademyBilling::DefaultBillingRules());
        AcademyBilling::JsonSubscriberStorage storage("JsonTestFiles/Subscribers.json", provider);

        std::vector<AcademyBilling::Subscriber> subscribers = storage.getAllSubscribers();
        EXPECT_EQ(2, subscribers.size());
        EXPECT_STREQ("+38(095)1112233", subscribers[0].getNumber().c_str());
        EXPECT_EQ(1250, subscribers[0].getBalance());
        EXPECT_EQ(3000, subscribers[0].getLastRefill().getMoney());
        EXPECT_STREQ("+38(099)3332211", subscribers[1].getNumber().c_str());
        EXPECT_EQ(4221, subscribers[1].getBalance());
        EXPECT_EQ(5000, subscribers[1].getLastRefill().getMoney());
    }

    TEST(JsonSubscriberStorageTests, testAddSubscriber)
    {
        AcademyBilling::BillingRulesProvider provider;
        provider.addRules("Default", &AcademyBilling::DefaultBillingRules());
        AcademyBilling::JsonSubscriberStorage storage("JsonTestFiles/Subscribers.json", provider);

        size_t count = storage.getAllSubscribers().size();
        storage.addSubscriber(AcademyBilling::Subscriber("+38(066)1112233", 0, provider.getRules("Default"), AcademyBilling::Refill(3000, 12345678)));
        size_t countAfterAddition = storage.getAllSubscribers().size();
        EXPECT_EQ(countAfterAddition, count + 1);
    }

    TEST(JsonSubscriberStorageTests, testFindSubscriber)
    {
        AcademyBilling::BillingRulesProvider provider;
        provider.addRules("Default", &AcademyBilling::DefaultBillingRules());
        AcademyBilling::JsonSubscriberStorage storage("JsonTestFiles/Subscribers.json", provider);

        EXPECT_TRUE(storage.findSubscriber("+38(099)0000000") == NULL);
        EXPECT_FALSE(storage.findSubscriber("+38(099)3332211") == NULL);
    }
}
