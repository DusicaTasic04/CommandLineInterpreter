#ifndef RM_H
#define RM_H

#include "Command.h"

class RM : public CommandFileManager {
public:

	// Constructor.
	RM(vector<Token> attributes, vector<Token> redirections);

	// Execution removes file from the given path, or reportes a problem if a file can't be deleted.
	virtual void execute() override;

protected:

private:


};

#endif
