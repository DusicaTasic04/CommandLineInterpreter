#ifndef PROMPT_H
#define PROMPT_H

#include "Command.h"

class Prompt : public CommandOneArgument {
public:

	// Constructor
	Prompt(vector<Token> attributes, vector<Token> redirections);

	// Executes the prompt command.
	virtual void executeCommandOneArgument() override;

protected:

	virtual bool mustHaveArgument() const override { return true; }
	virtual bool hasOutput() const override { return false; }
	
private:

};

#endif