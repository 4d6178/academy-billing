#include <stdexcept>

#include "BillingRulesProvider.h"

namespace AcademyBilling
{
    void  BillingRulesProvider::addRules(const std::string &name, BillingRules *rules)
    {
        if (rulesMap.find(name) != rulesMap.end()) {
            throw std::runtime_error("Rules with name " + name + " already exist");
        }
        rulesMap[name] = rules;
    }

    BillingRules* const BillingRulesProvider::getRules(const std::string &name)
    {
        if (rulesMap.find(name) == rulesMap.end()) {
            throw std::runtime_error("Rules with name " + name + " are not found");
        }
        return rulesMap[name];
    }
}
