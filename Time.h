#ifndef TIME_H
#define TIME_H

#include "Command.h"
#include <ctime>

class Time : public CommandZeroAttributes {
public:

	// Constructor
	Time(vector<Token> attributes, vector<Token> redirections);

	// Redefined. Calculates hours, minutes and seconds.
	virtual void execute() override;

protected:

	virtual bool hasOutput() const override { return true; }

private:
	int hours;
	int minutes;
	int seconds;
};

#endif
