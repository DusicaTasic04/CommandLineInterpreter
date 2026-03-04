#include "Interpreter.h"
#include "Exception.h"

#include <memory>

Interpreter::Interpreter(string sign) : commandPrompt(sign), pipe('|') {}

void Interpreter::setPromptCommand(string sign) {
	commandPrompt = sign;	
}

Interpreter* Interpreter::Instance() {
	static Interpreter interpreter;
	return &interpreter;
}

void Interpreter::setLine(string line) {
	this->line = line;
}

void Interpreter::catchLine() {
	cout << commandPrompt << " ";
	reader.readLine();
	line = reader.getLine();
}

void Interpreter::processLine() {
	LexicalException::checkLexicography(line);
	Parser::cutLine(line);
	if (line == "") return;
	
	pipe.splitPipeline(line);
	pipe.processLine();
}

void Interpreter::process() {
	try {
		catchLine();
		processLine();
	}
	catch (const exception& e) {
		cerr << "Error occurred: \a" << e.what() << "\n";
	}
}