#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include <algorithm>

#include "JsonSubscriberStorage.h"
#include "DateParser.h"

namespace AcademyBilling
{
    JsonSubscriberStorage::JsonSubscriberStorage(const std::string &jsonFilePath, BillingRules *rules) :
        rules(rules)
    {
        std::ifstream jsonFile(jsonFilePath);
        if (!jsonFile) {
            throw std::runtime_error("File " + jsonFilePath + " not found");
        }

        std::stringstream jsonText;
        std::copy(std::istreambuf_iterator<char>(jsonFile), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(jsonText));

        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(jsonText, root)) {
            throw std::runtime_error("File " + jsonFilePath + " is bad formatted");
        }
        jsonSubscribersArray = root["subscribers"];
        this->loadSubscribers();
    }

    void JsonSubscriberStorage::addSubscriber(const Subscriber &subscriber)
    {
        subscribers.push_back(subscriber);
    }

    void JsonSubscriberStorage::getAllSubscribers(std::vector<Subscriber> &subscribers)
    {
        subscribers = this->subscribers;
    }

    Subscriber* JsonSubscriberStorage::findSubscriber(const std::string &number)
    {
        for (size_t i = 0; i < subscribers.size(); ++i) {
            if (subscribers[i].getNumber() == number) {
                return &subscribers[i];
            }
        }
        return NULL;
    }

    JsonSubscriberStorage::~JsonSubscriberStorage(void)
    {
    }

    void JsonSubscriberStorage::loadSubscribers()
    {
        for (size_t i = 0; i < jsonSubscribersArray.size(); ++i) {
            std::string number = jsonSubscribersArray[i].get("number", "").asString();
            size_t balance = jsonSubscribersArray[i].get("balance", "0").asUInt();
            Refill refill = this->getFirstRefill(i);
            Subscriber subscriber(number, balance, rules, refill);
            subscribers.push_back(subscriber);
        }
    }

    Refill JsonSubscriberStorage::getFirstRefill(size_t subscriberIndex) const
    {
        const size_t firstRefillIndex = 0;
        Json::Value jsonFirstRefill = jsonSubscribersArray[subscriberIndex].get("events", "")[firstRefillIndex];
        if (jsonFirstRefill.get("type", "").asString() != "Refill") {
            throw std::runtime_error("First event should be a refill");
        }

        size_t firstRefillValue = jsonFirstRefill.get("value", "0").asUInt();
        std::string firstRefillDate = jsonFirstRefill.get("date", "").asString();
        DateParser dateParser(firstRefillDate);
        Refill refill(firstRefillValue, dateParser.parseDate());
        return refill;
    }
}