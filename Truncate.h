#ifndef TRUNCATE_H
#define TRUNCATE_H

#include "Command.h"

class Truncate : public CommandFileManager {
public:

	// Constructor
	Truncate(vector<Token> attributes, vector<Token> redirections);

	// Execution opens the file named 'filename' and deletes its content.
	virtual void execute() override;
};


#endif // !TRUNCATE_H
