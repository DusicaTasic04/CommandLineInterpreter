#include "Batch.h"
#include "Parser.h"

#include <sstream>

Batch::Batch(vector<Token> attributes, vector<Token> redirections) : 
	CommandOneArgument(), pipe('|') {
	setRedirections(redirections);
	setAttributes(attributes);
}

void Batch::process(string line) {
	try {
		LexicalException::checkLexicography(line);
		Parser::cutLine(line);
		if (line == "") return;
		pipe.splitPipeline(line);
		pipe.processLine();
	}
	catch (exception& e) {
		output += string("Error occurred: ") + e.what() + "\n";
	}
}

void Batch::executeCommandOneArgument() {
	string line;
	for (int i = 0; i < argument->size(); i++) {
		line += (*argument)[i];
		if ((*argument)[i] == '\n') {
			process(line);
			line = "";
		}
	}
	process(line);
}

void Batch::printOutput() const {
	if (!outputTarget) (cout) << output;
	else (*outputTarget) << output << flush;
}
