#ifndef ECHO_H
#define ECHO_H

#include "Command.h"

class Echo : public CommandOneArgument {
public:

	// Constructor
	Echo(vector<Token> attributes, vector<Token> redirections);

	// Executes one command. 
	// The result of an execution is the same input that was read. 
	virtual void executeCommandOneArgument() override;

protected:

	virtual bool mustHaveArgument() const override { return false; }
	virtual bool hasOutput() const override { return true; }

private:

};

#endif