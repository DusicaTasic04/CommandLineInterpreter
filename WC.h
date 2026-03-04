#ifndef WC_H
#define WC_H

#include "Command.h"

class WC : public CommandOptionArgument {
public:

	//Constructor.
	WC(vector<Token> attributes, vector<Token> redirections);

	// Executes one command. 
	// The result of an execution is the number of words/characters. 
	virtual void executeCommandOneArgument() override;

	// Calculates the number of characters in an argument.
	void charCount();

	// Calculates the number of words in an argument.
	void wordCount();

protected:

	virtual bool mustHaveArgument() const override { return false; }
	virtual bool hasOutput() const override { return true; }

private:
	unsigned int counter;
};


#endif // !WC_H

