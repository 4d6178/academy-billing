#pragma once
#include <string>
#include <time.h>

namespace AcademyBilling
{
	class Call
	{
	private:
		std::string callerNumber;
		std::string calleeNumber;
		time_t time;
		unsigned int duration;
	public:
		Call(const std::string& From,const std::string& To,const time_t& Time,const unsigned int& Duration);
		~Call(void);
		std::string getCallerNumber() const;
		void setCallerNumber(const std::string&);
		std::string getCalleeNumber() const;
		void setCalleeNumber(const std::string&);
		time_t getTime() const;
		void setTime(const time_t&);
		unsigned int getDuration() const;
		void setDuration(const unsigned int&);
	};
}
