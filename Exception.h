#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
#include <set>
#include <iostream>

using namespace std;

class Exception : public exception {
public:
	Exception(const string& msg);

	const char* what() const noexcept override;

protected:
	string message;
};

class LexicalException : public Exception {
public:
	static void checkLexicography(string line);

protected:
	LexicalException(const string& msg);

	static const set<char> forbiddenChars;
};

class UnknownCommandException : public Exception {
public:
	UnknownCommandException(string command);
};

class SyntaxException : public Exception {
public:
	static SyntaxException qmNotClosed();
	static SyntaxException qmMissing();
	static SyntaxException invalidPipeUsage();

protected:
	SyntaxException(const string& msg);
};

class RedirectionException : public Exception {
public:
	static RedirectionException unsupported();
	static RedirectionException unsupportedInput();
	static RedirectionException unsupportedOutput();

	static RedirectionException duplicateInput();
	static RedirectionException duplicateOutput();

	static RedirectionException missingArgument();
	static RedirectionException excessiveArguments();
	static RedirectionException unexpectedArgument();

protected:
	RedirectionException(const string& msg);
};

class FileException : public Exception {
public:
	static void checkFileAccessibility(string filename, ios::openmode mode);
	static void fileExists(string filename);

protected:
	FileException(const string& msg);
};

#endif // !EXCEPTION_H
