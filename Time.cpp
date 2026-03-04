#include "Time.h"

Time::Time(vector<Token> attributes, vector<Token> redirections) : 
    CommandZeroAttributes(), hours(0), minutes(0), seconds(0) { 
    setRedirections(redirections);
    setAttributes(attributes);
};

void Time::execute() {
    time_t now = time(nullptr);
    struct tm localTime;

    localtime_s(&localTime, &now);

    hours = localTime.tm_hour;
    minutes = localTime.tm_min;
    seconds = localTime.tm_sec;

    output = (hours < 10 ? "0" : "") + to_string(hours) + ":";
    output += (minutes < 10 ? "0" : "") + to_string(minutes) + ":";
    output += (seconds < 10 ? "0" : "") + to_string(seconds);
}

