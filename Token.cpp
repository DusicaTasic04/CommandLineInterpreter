#include "Echo.h"
#include "Prompt.h"
#include "Time.h"
#include "Date.h"
#include "Touch.h"
#include "Truncate.h"
#include "RM.h"
#include "WC.h"
#include "TR.h"
#include "Head.h"
#include "Batch.h"
#include "Token.h"
#include "Reader.h"

#include <exception>

class Command; 

Token::Token() { }

void Token::setElements(vector<string> input) {
	command = input[0];
	other = vector<string>(input.begin() + 1, input.end());
}

bool Token::hasQuotationMarks(const string& s) {
	return (s[0] == '"' && s[s.size() - 1] == '"');
}

void Token::removeQuotationMarks(string& argument) {
	if (!argument.size()) throw logic_error("Missing an argument.");
	if (!hasQuotationMarks(argument))
		throw logic_error("No quotation marks around an argument.");
	argument = argument.substr(1, argument.size() - 2);
}

string Token::requestArgument() const {
	string argument, s;
	while (std::getline(cin, s))
		argument += s + "\n";
	cin.ignore();
	cin.clear();
	return argument;
}

void Token::processArgument(string& argument) const {
	if (argument.empty()) {
		argument = requestArgument();
		return;
	}
	if (argument[0] == '"' and argument[argument.size() - 1] == '"')  {
		removeQuotationMarks(argument);
		return;
	}

	FReader f(argument);
	argument = f.readFile();
}

unique_ptr<Command> Token::createCommand() {
	if (command == commands[ECHO]) {
		processArgument(other[0]);
		unique_ptr<Echo> echo = make_unique<Echo>(other[0]);
		return echo;
	}
	else if (command == commands[PROMPT]) {
		removeQuotationMarks(other[0]);
		unique_ptr<Prompt> p = make_unique<Prompt>(other[0]);
		return p;
	}
	else if (command == commands[TIME]) {
		unique_ptr<Time> time = make_unique<Time>();
		return time;
	}
	else if (command == commands[DATE]) {
		unique_ptr<Date> date = make_unique<Date>();
		return date;
	}
	else if (command == commands[TOUCH]) {
		unique_ptr<Touch> touch = make_unique<Touch>(other[0]);
		return touch;
	}
	else if (command == commands[TRUNCATE]) {
		unique_ptr<Truncate> trunc = make_unique<Truncate>(other[0]);
		return trunc;
	}
	else if (command == commands[RM_]) {
		unique_ptr<RM> rm = make_unique<RM>(other[0]);
		return rm;
	}
	else if (command == commands[WC_]) {
		processArgument(other[1]);
		unique_ptr<WC> wc = make_unique<WC>(other[0], other[1]);
		return wc;
	}
	else if (command == commands[TR_]) { //
		if (hasQuotationMarks(other[0]) && hasQuotationMarks(other[1]) && hasQuotationMarks(other[2]) || 
				!hasQuotationMarks(other[0]) && hasQuotationMarks(other[1]) && hasQuotationMarks(other[2]) ) {
			processArgument(other[0]);
			removeQuotationMarks(other[1]);
			removeQuotationMarks(other[2]);
			unique_ptr<TR> tr = make_unique<TR>(other[0], other[1], other[2]);
			return tr;
		}
		if (hasQuotationMarks(other[0]) && hasQuotationMarks(other[1]) || 
				!hasQuotationMarks(other[0]) && hasQuotationMarks(other[1])) {
			processArgument(other[0]);
			removeQuotationMarks(other[1]);
			unique_ptr<TR> tr = make_unique<TR>(other[0], other[1], "");
			return tr;
		}
		if (hasQuotationMarks(other[0])) {
			removeQuotationMarks(other[0]);
			unique_ptr<TR> tr = make_unique<TR>(requestArgument(), other[0], "");
			return tr;
		}
		else
			throw logic_error("Semantic error.");
	}
	else if (command == commands[HEAD]) {
		processArgument(other[1]);
		unique_ptr<Head> head = make_unique<Head>(other[0], other[1]);
		return head;
	}
	else if (command == commands[BATCH]) {
		processArgument(other[0]);
		unique_ptr<Batch> batch = make_unique<Batch>(other[0]);
		return batch;
	}
	else {
		throw logic_error("command \"" + command + "\" not found");
	}
}

const string Token::commands[commandsNumber] = { "echo", "prompt", "time",	"date", "touch", "truncate",
	"rm", "wc", "tr", "head", "batch" };
