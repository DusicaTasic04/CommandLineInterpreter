#ifndef TOUCH_H
#define TOUCH_H

#include "Command.h"

class Touch : public CommandFileManager {
public:

	// Constructor
	Touch(vector<Token> attributes, vector<Token> redirections);

	virtual void execute() override;

protected:

private:

};


#endif // !TOUCH_H