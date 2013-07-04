#include "Subscriber.h"

namespace AcademyBilling
{
	Subscriber::Subscriber(const std::string& s)
	{
	}

	Subscriber::~Subscriber(void)
	{
	}

	int Subscriber::getBalance() const
	{
		return 1;
	}

	std::string Subscriber::getNumber() const
	{
		return "+38(050)1234567";
	}

	int Subscriber::charge(const int&)
	{
		return 1;
	}

	int Subscriber::addRefill(const Refill& refill)
	{
		return 1;
	}
}