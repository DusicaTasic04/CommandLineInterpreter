#include "RM.h"
#include <cstdio>

RM::RM(vector<Token> attributes, vector<Token> redirections) : 
	CommandFileManager() { 
	setRedirections(redirections);
	setAttributes(attributes);
}

void RM::execute() {
	if (remove(filename.c_str()) != 0)
		throw system_error(errno, generic_category(), filename);
}

