#ifndef TOKEN_PROCESSOR
#define TOKEN_PROCESSOR

#include "Command.h"
#include <vector>

enum ECommand {
	ECHO, PROMPT, TIME,	DATE, TOUCH, TRUNCATE, RM_, WC_, TR_, HEAD, BATCH
};

// Creates the right type of the command.
class TokenProcessor {
public:

	// Constructor.
	TokenProcessor();

	// Sets the input as a command and as other given parameters.
	void setElements(vector<Token> input);

	// Creates the right type of the command and returns it.
	unique_ptr<Command> createCommand();

private:
	static const unsigned int commandsNumber = 11;
	string command;
	vector<Token> attributes;
	vector<Token> redirections;
	static const string commands[commandsNumber];
};

#endif // !TOKEN_PROCESSOR
