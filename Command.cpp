#include "Command.h"
#include "Reader.h"
#include <iostream>

Command::Command() : outputTarget(nullptr), output("") {}

void Command::printOutput() const {
	if (!this->hasOutput()) return;

	if (!outputTarget) (cout) << output << "\n";
	else (*outputTarget) << output << "\n" << flush ;
}

void Command::setRedirections(vector<Token> redirections) {
	if (!this->hasOutput() && redirections.size())
		throw RedirectionException::unsupported();
	for (int i = 0; i < redirections.size(); i++) {
		if (redirections[i].getType() == Token::INPUT_REDIRECTION)
			throw RedirectionException::unsupportedInput();
		if (redirections[i].getType() == Token::OUTPUT_REDIRECTION) {
			processOutputRedirection(redirections[i]);
			continue;
		}
		if (redirections[i].getType() == Token::OUTPUT_REDIRECTION_APPEND) {
			processOutputRedirectionAppend(redirections[i]);
			continue;
		}
	}
}

void Command::processOutputRedirection(Token redirection) {
	if (!this->hasOutput()) throw RedirectionException::unsupportedOutput();
	auto mode = ios::out | ios::trunc;
	string filename = redirection.getValue().substr(1, redirection.getValue().size() - 1);

	FileException::checkFileAccessibility(filename, mode);
	setOutputTarget(new ofstream(filename, mode));
}

void Command::processOutputRedirectionAppend(Token redirection) {
	if (!this->hasOutput()) throw RedirectionException::unsupportedOutput();
	auto mode = ios::out | ios::app;
	string filename = redirection.getValue().substr(2, redirection.getValue().size() - 2);

	FileException::checkFileAccessibility(filename, mode);
	setOutputTarget(new ofstream(filename, mode));
}

void Command::setOutputTarget(ostream* out) {
	if (!this->hasOutput())	
		throw RedirectionException::unsupportedOutput();	// Should not set redirection to the command which
	if (this->outputTarget)									// does not return output.
		throw RedirectionException::duplicateOutput();
	outputTarget = out;
}

Command::~Command() { }

CommandZeroAttributes::CommandZeroAttributes() : Command() { }

void CommandZeroAttributes::setAttributes(vector<Token> attributes) {
	if (attributes.size()) throw RedirectionException::unexpectedArgument();
}

CommandFileManager::CommandFileManager() : Command() { }

void CommandFileManager::setAttributes(vector<Token> attributes) {
	if (!attributes.size()) throw RedirectionException::missingArgument();
	if (attributes.size() > 1) throw RedirectionException::excessiveArguments();
	this->filename = attributes[0].getValue();
}

CommandOneArgument::CommandOneArgument() : Command(), argument(nullptr) { }

void CommandOneArgument::execute() {
	if (!this->argument && !this->mustHaveArgument()) requestArgument();
	executeCommandOneArgument();
}

void CommandOneArgument::setArgument(string arg) {
	if (this->argument)
		throw RedirectionException::duplicateInput();	// User is trying to override an existing argument.
	this->argument = new string(arg);
}

void CommandOneArgument::removeQM(string& argument) {
	argument = argument.substr(1, argument.size() - 2);
}

void CommandOneArgument::setArgumentQM(string argument) {
	removeQM(argument);
	setArgument(argument);
}

void CommandOneArgument::readArgumentFromFile(string filename) {
	FReader f(filename);
	setArgument(f.readUntilEOF());
}

void CommandOneArgument::requestArgument() {
	CReader c;
	setArgument(c.readUntilEOF());
}

void CommandOneArgument::processArgument(Token arg) {
	if (arg.getType() == Token::ARGUMENT_QM)
		setArgumentQM(arg.getValue());
	else if (!this->mustHaveArgument())
		readArgumentFromFile(arg.getValue());
	else throw SyntaxException::qmMissing();
}

void CommandOneArgument::setAttributes(vector<Token> attributes) { 
	if (attributes.size() > 1) 
		throw RedirectionException::excessiveArguments();
	if (!attributes.size() && this->mustHaveArgument())
		throw RedirectionException::missingArgument();
	if (attributes.size())
		processArgument(attributes[0]);
}

void CommandOneArgument::processInputRedirection(Token redirection) {
	if (this->mustHaveArgument()) throw RedirectionException::unsupportedInput();
	string filename = redirection.getValue().substr(1, redirection.getValue().size() - 1);
	readArgumentFromFile(filename);
}

void CommandOneArgument::setRedirections(vector<Token> redirections) {
	for (int i = 0; i < redirections.size(); i++) {
		if (redirections[i].getType() == Token::INPUT_REDIRECTION) {
			processInputRedirection(redirections[i]);
			continue;
		}
		if (redirections[i].getType() == Token::OUTPUT_REDIRECTION) {
			processOutputRedirection(redirections[i]);
			continue;
		}
		if (redirections[i].getType() == Token::OUTPUT_REDIRECTION_APPEND) {
			processOutputRedirectionAppend(redirections[i]);
			continue;
		}
	}
}

CommandOneArgument::~CommandOneArgument() {
	delete argument;
}

CommandOptionArgument::CommandOptionArgument() : 
	CommandOneArgument() { }

void CommandOptionArgument::setAttributes(vector<Token> attributes) {
	if (!attributes.size() || (attributes.size() == 1 && this->mustHaveArgument()))
		throw RedirectionException::missingArgument();
	if (attributes.size() > 2) 
		throw RedirectionException::excessiveArguments();
	if (attributes[0].getType() != Token::OPTION) 
		throw Exception("wrong option format");
	this->option = attributes[0].getValue();
	if (attributes.size() == 2)
		processArgument(attributes[1]);
}

CommandArgumentWhatWith::CommandArgumentWhatWith()
	: CommandOneArgument() { }

void CommandArgumentWhatWith::setWhatWith(string what, string with) {
	removeQM(what);
	removeQM(with);
	this->what = what;
	this->with = with;
}

void CommandArgumentWhatWith::setAttributes(vector<Token> attributes) {
	if (!attributes.size()) throw Exception("an attribute <what> is missing. ");
	if (attributes.size() > 3) throw RedirectionException::excessiveArguments();
	string what, with;
	if (attributes.size() == 1) {
		if (attributes[0].getType() != Token::ARGUMENT_QM)
			throw Exception("attribute <what> must be under quotation marks. ");
		setWhatWith(attributes[0].getValue(), "\"\"");
	}
	else if (attributes.size() == 2) {
		if (attributes[0].getType() != Token::ARGUMENT_QM)
			throw Exception("attribute <what> must be under quotation marks. ");
		if (attributes[1].getType() != Token::ARGUMENT_QM)
			throw Exception("attribute <with> must be under quotation marks. ");
		setWhatWith(attributes[0].getValue(), attributes[1].getValue());
	}
	else {
		if (attributes[0].getType() != Token::ARGUMENT_QM)
			throw Exception("attribute <what> must be under quotation marks. ");
		if (attributes[1].getType() != Token::ARGUMENT_QM)
			throw Exception("attribute <with> must be under quotation marks. ");
		processArgument(attributes[0]);
		setWhatWith(attributes[1].getValue(), attributes[2].getValue());
	}
}
