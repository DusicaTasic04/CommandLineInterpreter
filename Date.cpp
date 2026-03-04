#include "Date.h"

Date::Date(vector<Token> attributes, vector<Token> redirections) : 
	CommandZeroAttributes(), day(1), month(1), year(2000) { 
	setRedirections(redirections);
	setAttributes(attributes);
}

void Date::execute() {
	time_t now = time(nullptr); 
	struct tm localTime;

	localtime_s(&localTime, &now);

	day = localTime.tm_mday;
	month = localTime.tm_mon + 1;
	year = 1900 + localTime.tm_year;

	output = (to_string(day) + "." + to_string(month) + "." + to_string(year) + ".");
}
