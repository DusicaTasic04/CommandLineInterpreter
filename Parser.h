#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <vector>

#include "Token.h"

using namespace std;

class Parser {
public:

	// Constructor.
	Parser();

	// Cuts the line based of the given maximal line lenght.
	static void cutLine(string& line);

	// Divides the line on tokens and returns them.
	static vector<Token> parseLine(string& line);

private:
	// Skips spaces and places a counter after the last space.
	static void skipSpaces(string line, int& cnt);

	// Catches text starting at a given counter and ending with a space.
	static void catchUntilSpace(string line, string& text, int& cnt);

	// Catches text contained within quotation marks.
	static void catchQM(string line, string& text, int& cnt);

	// Catches the filename representing the input/output redirection.
	static void catchRedirection(string line, string& text, int& cnt);

	// Catches the filename representing the output append redirection.
	static void catchRedirectionAppend(string line, string& text, int& cnt);

	static const unsigned int maxLineLength = 256;

};


#endif // !PARSER_H
