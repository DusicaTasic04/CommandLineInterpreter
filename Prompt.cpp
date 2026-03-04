#include "Prompt.h"
#include "Interpreter.h"

Prompt::Prompt(vector<Token> attributes, vector<Token> redirections) : 
	CommandOneArgument() { 
	setRedirections(redirections);
	setAttributes(attributes);
}

class Interpreter;

void Prompt::executeCommandOneArgument() {
	Interpreter::Instance()->setPromptCommand(*argument);
}