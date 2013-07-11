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
    JsonSubscriberStorage::JsonSubscriberStorage(const std::string &jsonFilePath, BillingRulesProvider &provider) :
        rulesProvider(&provider)
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
        if (jsonSubscribersArray.isNull() || !jsonSubscribersArray.isArray()) {
            throw std::runtime_error("Field \"subscribers\" not found or not an array");
        }
        this->loadSubscribers();
    }

    void JsonSubscriberStorage::addSubscriber(const Subscriber &subscriber)
    {
        subscribers.push_back(subscriber);
    }

    const std::vector<Subscriber>& JsonSubscriberStorage::getAllSubscribers() const
    {
        return subscribers;
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
            Json::Value jsonNumber = jsonSubscribersArray[i].get("number", "");
            if (jsonNumber.isNull()) {
                throw std::runtime_error("Field \"number\" not found");
            }
            Json::Value jsonBalance = jsonSubscribersArray[i].get("balance", "0");
            if (jsonBalance.isNull()) {
                throw std::runtime_error("Field \"balance\" not found");
            }
            Json::Value jsonTariff = jsonSubscribersArray[i].get("tariff", "");
            if (jsonTariff.isNull()) {
                throw std::runtime_error("Field \"tariff\" not found");
            }

            std::string number = jsonNumber.asString();
            size_t balance = jsonBalance.asUInt();
            Refill refill = this->getFirstRefill(i);
            BillingRules *rules = rulesProvider->getRules(jsonTariff.asString());
            Subscriber subscriber(number, balance, rules, refill);
            subscribers.push_back(subscriber);
        }
    }

    Refill JsonSubscriberStorage::getFirstRefill(size_t subscriberIndex) const
    {
        Json::Value jsonEventsArray = jsonSubscribersArray[subscriberIndex].get("events", "");
        if (jsonEventsArray.isNull() || !jsonEventsArray.isArray()) {
            throw std::runtime_error("Field \"events\" not found or not an array");
        }

        const size_t firstRefillIndex = 0;
        Json::Value jsonFirstRefill = jsonEventsArray[firstRefillIndex];
        if (jsonFirstRefill.isNull() || jsonFirstRefill.get("type", "").asString() != "Refill") {
            throw std::runtime_error("First event should be a refill");
        }

        Json::Value jsonFirstRefillValue = jsonFirstRefill.get("value", "0");
        if (jsonFirstRefillValue.isNull()) {
            throw std::runtime_error("Field \"value\" not found");
        }
        Json::Value jsonFirstRefillDate = jsonFirstRefill.get("date", "");
        if (jsonFirstRefillDate.isNull()) {
            throw std::runtime_error("Field \"date\" not found");
        }

        size_t firstRefillValue = jsonFirstRefillValue.asUInt();
        std::string firstRefillDate = jsonFirstRefillDate.asString();
        DateParser dateParser(firstRefillDate);
        Refill refill(firstRefillValue, dateParser.parseDate());
        return refill;
    }
}