#ifndef DATE_H
#define DATE_H

#include "Command.h"

class Date : public CommandZeroAttributes {
public:

	// Constructor
	Date(vector<Token> attributes, vector<Token> redirections);

	// Calculates the day, month and year.
	virtual void execute() override;

protected:

	virtual bool hasOutput() const override { return true; }

private:
	int day;
	int month;
	int year;
};

#endif // !DATE_H

