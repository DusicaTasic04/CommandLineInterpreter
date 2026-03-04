#ifndef TR_H
#define TR_H

#include "Command.h"

class TR : public CommandArgumentWhatWith {
public:
	TR(vector<Token> attributes, vector<Token> redirections);

	virtual void executeCommandOneArgument() override;

protected:

	virtual bool mustHaveArgument() const override { return false; }
	virtual bool hasOutput() const override { return true; }
};

#endif // !TR_H
