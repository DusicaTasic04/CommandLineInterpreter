#ifndef PIPE_H
#define PIPE_H

#include <list>
#include "Command.h"
#include "TokenProcessor.h"

using namespace std;

class Pipe {

public:

	Pipe(char delimiter);

	// Splits the given line on strings which are further 
	// processed into commands.
	void splitPipeline(string line);

	void setCommand(string segment);

	// Processes a full input line by splitting it into commands 
	// and executing each in order.
	void processLine();

private:
	TokenProcessor tokenProcessor;
	char delimiter;

	list<unique_ptr<Command>> commands;
};

#endif // !PIPE_H
