#ifndef BATCH_H
#define BATCH_H

#include "Command.h"
#include "Pipe.h"

class Batch : public CommandOneArgument {
public:

	// Constructor.
	Batch(vector<Token> attributes, vector<Token> redirections);

	// From a given argument, reads line by line and executes them 
	// as they are commands.
	virtual void executeCommandOneArgument() override;

	// Processes a line as a command.
	void process(string line);

	// Prints the output of the command on the given output target,
	// if null prints the output on the cout. 
	virtual void printOutput() const override;

protected:

	virtual bool mustHaveArgument() const override { return false; }
	virtual bool hasOutput() const override { return true; }

private:
	Pipe pipe;
};

#endif // BATCH_H