#include "Call.h"

namespace AcademyBilling
{
	Call::Call(const std::string& From,const std::string& To,const time_t& Time,const unsigned int& Duration)
	{
	}

	Call::~Call(void)
	{
	}

	std::string Call::getCallerNumber() const
	{
		return "+38(050)1234567";
	}

	std::string Call::getCalleeNumber() const
	{
		return "+38(050)1234568";
	}

	time_t Call::getTime() const
	{
		return 414086872;
	}

	unsigned int Call::getDuration() const
	{
		return 1;
	}
}