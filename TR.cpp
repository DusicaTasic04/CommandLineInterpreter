#include "TR.h"

TR::TR(vector<Token> attributes, vector<Token> redirections) : 
	CommandArgumentWhatWith() { 
	setRedirections(redirections);
	setAttributes(attributes);
}

void TR::executeCommandOneArgument() {
	if (!what.size()) throw Exception("field <what> cannot be empty. ");
    if (with.size() > argument->size()) return; // It sure won't find a 'with' string inside of an argument.

    const string& arg = *argument; 

    for (size_t i = 0; i < arg.size(); ) {
        if (arg.compare(i, what.size(), what) == 0) {
            output += with;
            i += what.size();
        }
        else 
            output += arg[i++];
    }
}
