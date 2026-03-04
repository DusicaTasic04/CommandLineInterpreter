#ifndef HEAD_H
#define HEAD_H

#include "Command.h"

class Head : public CommandOptionArgument {
public:

	// Constructor.
	Head(vector<Token> attributes, vector<Token> redirections);

	// Execution will print the first N lines from a given argument.
	virtual void executeCommandOneArgument() override;

	// Prints the output of the command on the given output target,
	// if null prints the output on the cout. 
	virtual void printOutput() const override;
protected:

	// Gets the number of rows which needs to be echoed.
	int getCount();

	virtual bool mustHaveArgument() const override { return false; }
	virtual bool hasOutput() const override { return true; }
};

#endif
