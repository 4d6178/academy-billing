#include "DefaultBillingRulesTests.h"

#include <DefaultBillingRules.h>
#include <Call.h>
#include <Refill.h>

namespace AcademyBillingTesting
{
    TEST_F(DefaultBillingRulesTests, default_billing_rules_weekend_calls)
    {
        std::auto_ptr<AcademyBilling::DefaultBillingRules> rules(new AcademyBilling::DefaultBillingRules());

        // This day is Saturday.
        tm timeTm;
        timeTm.tm_year=2013-1900;
        timeTm.tm_mon = 00;
        timeTm.tm_mday = 05;
        timeTm.tm_hour = 00;
        timeTm.tm_min = 00;
        timeTm.tm_sec = 00;
        timeTm.tm_isdst = 0;
        
        time_t timeT = mktime(&timeTm);

        int balance = 5000;
        AcademyBilling::Subscriber subscriber("+38(095)0112233", balance, rules.get(), AcademyBilling::Refill(10,timeT-100)); 
        
        // 5 first free minutes on weekend cover it
        AcademyBilling::Call call1("+38(095)0112233", "+38(095)0112233", timeT, 10);
        rules->chargeForCall(call1, subscriber);
        // Only conection.
        balance -= 33;
        ASSERT_EQ(balance, subscriber.getBalance());

        // Exectly one minute to other network.
        AcademyBilling::Call call2("+38(095)0112233", "+38(062)0112233", timeT += 100, 60);
        rules->chargeForCall(call2, subscriber);
        // 33 - for connection, 95 - minute.
        balance -= (33 + 95);
        ASSERT_EQ(balance, subscriber.getBalance());

        // 5 first free minutes + 30 minutes after refill + 1 second.
        AcademyBilling::Call call3("+38(095)0112233", "+38(095)0112233", timeT += 3600, (5+30)*60+1);
        rules->chargeForCall(call3, subscriber);
        // 33 - for connection, 50 - minute.
        balance -= (33 + 50);
        ASSERT_EQ(balance, subscriber.getBalance());

        // 5 first free minutes + 61 second, when 30 minutes are used.
        AcademyBilling::Call call4("+38(095)0112233", "+38(095)0112233", timeT += 3600, 60*5 + 61);
        rules->chargeForCall(call4, subscriber);
        // 33 - for connection, 50*2 - for 2 minutes.
        balance -= (33 + 50*2);
        ASSERT_EQ(balance, subscriber.getBalance());

        // Refilling balance (100).
        AcademyBilling::Refill refill(100, timeT += 3600);
        subscriber.addRefill(refill);
        balance += 100;
        ASSERT_EQ(balance, subscriber.getBalance());

        // 5 first free minutes + 61 second, should be covered by free minutes
        AcademyBilling::Call call5("+38(095)0112233", "+38(095)0112233", timeT += 3600, 60*5 + 61);
        rules->chargeForCall(call5, subscriber);
        // 33 - for connection.
        balance -= 33;
        ASSERT_EQ(balance, subscriber.getBalance());
    }

    TEST_F(DefaultBillingRulesTests, default_billing_rules_workday_calls)
    {
        std::auto_ptr<AcademyBilling::DefaultBillingRules> rules(new AcademyBilling::DefaultBillingRules());

        // This day is Tuesday.
        tm timeTm;
        timeTm.tm_year=2013-1900;
        timeTm.tm_mon = 00;
        timeTm.tm_mday = 01;
        timeTm.tm_hour = 00;
        timeTm.tm_min = 00;
        timeTm.tm_sec = 00;
        timeTm.tm_isdst = 0;
        
        time_t timeT = mktime(&timeTm);

        int balance = 5000;
        AcademyBilling::Subscriber subscriber("+38(095)0112233", balance, rules.get(), AcademyBilling::Refill(10, timeT-100)); 
        
        // 10 seconds call. Covered by one minute of 30 free minutes
        AcademyBilling::Call call1("+38(095)0112233", "+38(099)0112233", timeT, 10);
        rules->chargeForCall(call1, subscriber);
        // Only conection.
        balance -= 33;
        ASSERT_EQ(balance, subscriber.getBalance());

        // Exactly one minute to other network.
        AcademyBilling::Call call2("+38(095)0112233", "+38(062)0112233", timeT += 100, 60);
        rules->chargeForCall(call2, subscriber);
        // 33 - for connection, 95 - minute.
        balance -= (33 + 95);
        ASSERT_EQ(balance, subscriber.getBalance());

        // 29 minutes after refill (1 was already used) + 1 second.
        AcademyBilling::Call call3("+38(095)0112233", "+38(095)0112233", timeT += 3600, 29 * 60+1);
        rules->chargeForCall(call3, subscriber);
        // 33 - for connection, 50 - minute.
        balance -= (33 + 50);
        ASSERT_EQ(balance, subscriber.getBalance());

        // 61 second, all 30 minutes are already used.
        AcademyBilling::Call call4("+38(095)0112233", "+38(066)0112233", timeT += 3600, 61);
        rules->chargeForCall(call4, subscriber);
        // 33 - for connection, 50*2 - for 2 minutes.
        balance -= (33 + 50*2);
        ASSERT_EQ(balance, subscriber.getBalance());

        // Refilling balance (100).
        AcademyBilling::Refill refill(100, timeT += 3600);
        subscriber.addRefill(refill);
        balance += 100;
        ASSERT_EQ(balance, subscriber.getBalance());

        // 37:01 minutes, 30 should be covered by free minutes, 8 - payed.
        AcademyBilling::Call call5("+38(095)0112233", "+38(095)0112233", timeT += 3600, 60 * 37 + 1);
        rules->chargeForCall(call5, subscriber);
        // 33 - for connection, 8*50 for 8 minutes.
        balance -= (33 + 8*50);
        ASSERT_EQ(balance, subscriber.getBalance());
    }

    TEST_F(DefaultBillingRulesTests, default_billing_rules_refill_expired)
    {
        std::auto_ptr<AcademyBilling::DefaultBillingRules> rules(new AcademyBilling::DefaultBillingRules());

        // This day is Tuesday.
        tm timeTm;
        timeTm.tm_year=2013-1900;
        timeTm.tm_mon = 00;
        timeTm.tm_mday = 01;
        timeTm.tm_hour = 10;
        timeTm.tm_min = 10;
        timeTm.tm_sec = 20;
        timeTm.tm_isdst = 0;
        
        time_t timeT = mktime(&timeTm);

        int balance = 2000;
        int secondsIn30Days = 30 * 24 * 60 * 60;
        AcademyBilling::Subscriber subscriber("+38(095)0112233", balance, rules.get(), AcademyBilling::Refill(10, timeT));
        
        // Wait ten seconds
        timeT+=10;

        // Make 3:01 call. Covered by 4 free minutes
        AcademyBilling::Call call1("+38(095)0112233", "+38(066)0112233", timeT, 4 * 60);
        rules->chargeForCall(call1, subscriber);
        // Conection only.
        balance -= 33;
        ASSERT_EQ(balance, subscriber.getBalance());

        //Wait one hour less, then it'l take for minures to expire. It'l be Wednesday.
        timeT += secondsIn30Days - 3600;
        // Make 7:00 call.
        AcademyBilling::Call call2("+38(095)0112233", "+38(050)0112233", timeT, 7 * 60);
        rules->chargeForCall(call2, subscriber);
        // Conection only.
        balance -= 33;
        ASSERT_EQ(balance, subscriber.getBalance());

        //Wait one hour. Free minutes should expire.
        timeT += 3600;

        // Make 4:59 call.
        AcademyBilling::Call call3("+38(095)0112233", "+38(099)0112233", timeT, 4 * 60 + 59);
        rules->chargeForCall(call3, subscriber);
        // 33 - for connection, 50*5 - for 5 minutes.
        balance -= (33 + 50 * 5);
        ASSERT_EQ(balance, subscriber.getBalance());
    }

    TEST_F(DefaultBillingRulesTests, default_billing_rules_other_networks)
    {
        std::auto_ptr<AcademyBilling::DefaultBillingRules> rules(new AcademyBilling::DefaultBillingRules());

        // This day is Friday.
        tm timeTm;
        timeTm.tm_year=2013-1900;
        timeTm.tm_mon = 04;
        timeTm.tm_mday = 03;
        timeTm.tm_hour = 10;
        timeTm.tm_min = 10;
        timeTm.tm_sec = 20;
        timeTm.tm_isdst = 0;
        
        time_t timeT = mktime(&timeTm);

        int balance = 4000;
        AcademyBilling::Subscriber subscriber("+38(050)0112233", balance, rules.get(), AcademyBilling::Refill(4000, timeT));
        
        // 5 minutes to other network.
        AcademyBilling::Call call1("+38(050)0112233", "+38(096)0112233", timeT += 1000, 5 * 60);
        rules->chargeForCall(call1, subscriber);
        // 33 - for connection, 95 - 5 minutes.
        balance -= (33 + 5*95);
        ASSERT_EQ(balance, subscriber.getBalance());

        // 1 second to other network.
        AcademyBilling::Call call2("+38(050)0112233", "+38(060)0112233", timeT += 1000, 1);
        rules->chargeForCall(call2, subscriber);
        // 33 - for connection, 95 - 1 minute.
        balance -= (33 + 95);
        ASSERT_EQ(balance, subscriber.getBalance());

        // 3:01 to other network.
        AcademyBilling::Call call3("+38(050)0112233", "+38(063)0112233", timeT += 1000, 3 * 60 + 1);
        rules->chargeForCall(call3, subscriber);
        // 33 - for connection, 95*4 - 4 minutes.
        balance -= (33 + 95 * 4);
        ASSERT_EQ(balance, subscriber.getBalance());

        // 5:59 to other network.
        AcademyBilling::Call call4("+38(050)0112233", "+38(122)0112233", timeT += 1000, 5 * 60 + 59);
        rules->chargeForCall(call4, subscriber);
        // 33 - for connection, 6 * 95 - 6 minutes.
        balance -= (33 + 6 * 95);
        ASSERT_EQ(balance, subscriber.getBalance());
    }
}