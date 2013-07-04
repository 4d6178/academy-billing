#pragma once
#include <time.h>

namespace AcademyBilling
{
	class Refill
	{
	private:	
		int money;
		time_t time;
	public:	
		Refill(int,time_t);
		~Refill(void);
		int getMoney() const;
		void setMoney(const int&);
		time_t getTime() const;
		void setTime(const time_t&);
	};
}