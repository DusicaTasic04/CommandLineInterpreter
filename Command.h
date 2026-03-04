#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Token.h"
#include "Exception.h"

using namespace std;

// Interface of a command. Abstract.
class ICommand {
protected:

	// Constructor of an abstract class.
	ICommand() { }

	// Command must have an argument?
	// If not, the user must specify a file/redirection from which the 
	// argument is read, or enter the argument in subsequent lines.
	virtual bool mustHaveArgument() const = 0;
	
	// Command returns output?
	virtual bool hasOutput() const = 0;
};

// Abstract class of a command.
class Command : public ICommand {
public:

	// Virtual. Simulates the execution of one command.
	virtual void execute() = 0;

	// Prints the output of the command on the given output target,
	// if null prints the output on the cout. 
	virtual void printOutput() const;

	// Sets the output target of the command. 
	virtual void setOutputTarget(ostream* out);

	// Destructor.
	virtual ~Command();
	
protected:

	// Constructor of an abstract class.
	Command();

	// Sets the arguments, options ext. 
	virtual void setAttributes(vector<Token> attributes) = 0;

	// Sets the redirections. 
	virtual void setRedirections(vector<Token> redirections);

	// Handles the given input redirection and loads the argument given in the file.
	virtual void processOutputRedirection(Token redirection);

	// Handles the given input redirection and loads the argument given in the file.
	virtual void processOutputRedirectionAppend(Token redirection);

	ostream* outputTarget;

	string output;
};

// Abstract class of a command which does not take 
// input arguments or options. 
class CommandZeroAttributes : public Command {
protected:
	// Constructor of an abstract class.
	CommandZeroAttributes();

	// Sets the arguments, options ext. 
	// This kind of command does not take any input. 
	virtual void setAttributes(vector<Token> attributes) override;

	virtual bool mustHaveArgument() const override { return false; }
};


// Abstract class of a command which only takes a filename
class CommandFileManager : public Command {
protected:
	CommandFileManager();

	string filename;

	// Sets the arguments, options ext. 
	virtual void setAttributes(vector<Token> attributes) override;

	virtual bool mustHaveArgument() const override { return true; }
	virtual bool hasOutput() const override { return false; }
};

// Abstract class of a command which contains only one argument.
class CommandOneArgument : public Command {
public:
	// Sets the argument to the given value.
	void setArgument(string arg);

	// Runs the execution and requests the argument if not given.
	virtual void execute() override;

	// Runs the execution of this type of command.
	virtual void executeCommandOneArgument() = 0;

	// Destructor. Deletes the memory allocated by an argument.
	virtual ~CommandOneArgument() override;

protected:
	
	// Constructor of an abstract class.
	CommandOneArgument();

	// Sets the arguments, options ext. 
	virtual void setAttributes(vector<Token> attributes) override;

	// Sets the redirections. 
	virtual void setRedirections(vector<Token> redirections) override;

	// The only argument which is needed for this type of commands.
	string* argument;

	// Removes quotation marks around an argument by changing the original string
	virtual void removeQM(string& argument);

	// Removes quotation marks around an argument and sets it as an argument. 
	virtual void setArgumentQM(string argument);
	
	// Reads an argument from a given file
	virtual void readArgumentFromFile(string filename);

	// Requests an argument if missing.
	virtual void requestArgument();

	// Reads an argument and sets it. 
	virtual void processArgument(Token arg);

	// Handles the given input redirection and loads the argument given in the file.
	virtual void processInputRedirection(Token redirection);
	
private:

};

// Abstract class of a command which contains argument and an option.
class CommandOptionArgument : public CommandOneArgument {
public:
protected:

	// Constructor.
	CommandOptionArgument();

	// Sets the arguments, options ext. 
	virtual void setAttributes(vector<Token> attributes) override;

	string option;

private:

};

// Abstract class of a command which takes arguments, whit and what attribute.
class CommandArgumentWhatWith : public CommandOneArgument {
public:
protected:
	//Constructor.
	CommandArgumentWhatWith();

	// Sets what and with attributes, validating their state. 
	virtual void setWhatWith(string what, string with);

	// Sets the arguments, options ext. 
	virtual void setAttributes(vector<Token> attributes) override;

	string what;
	string with;
};

#endif
