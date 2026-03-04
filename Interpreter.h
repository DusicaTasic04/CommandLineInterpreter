#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <iostream>

#include "TokenProcessor.h"
#include "Reader.h"
#include "Parser.h"
#include "Pipe.h"

using namespace std;

class Interpreter {
public:
	
	// Returns the singleton instance of this class 
	static Interpreter* Instance();

	void setLine(string line);

	// Sets the command prompt. 
	void setPromptCommand(string sign);

	// Catches one line and returns it to be further processed.
	void catchLine();

	// Process a single line.
	void processLine();

	// Simulates the processing of one line.
	void process();

protected:
	// Constructor of the singleton.
	Interpreter(string sign = "$");

private:
	
	CReader reader;
	TokenProcessor tokenProcessor;
	Pipe pipe;

	string commandPrompt;
	string line;
};

#endif
