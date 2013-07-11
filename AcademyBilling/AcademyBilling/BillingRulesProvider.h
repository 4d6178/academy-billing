#pragma once
#include <map>
#include <string>

#include "BillingRules.h"

namespace AcademyBilling
{
    class BillingRulesProvider
    {
    public:
        void addRules(const std::string &name, BillingRules *rules);
        BillingRules* const getRules(const std::string &name);

    private:
        std::map<std::string, BillingRules*> rulesMap;
    };
}