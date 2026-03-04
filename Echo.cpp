#include "Echo.h"

Echo::Echo(vector<Token> attributes, vector<Token> redirections) : 
	CommandOneArgument() { 
	setRedirections(redirections);
	setAttributes(attributes);
}

void Echo::executeCommandOneArgument() {
	output = *argument;
}
