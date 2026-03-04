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
#include "TokenProcessor.h"
#include "Reader.h"

#include "Exception.h" 

class Command; 

TokenProcessor::TokenProcessor() { }

void TokenProcessor::setElements(vector<Token> input) {
	attributes.clear();
	redirections.clear();
	command = input[0].getValue();
	bool b = false;
	for (int i = 1; i < input.size(); i++) {
		if (input[i].getType() < Token::INPUT_REDIRECTION && !b)
			attributes.push_back(input[i]);
		else if (input[i].getType() >= Token::INPUT_REDIRECTION) {
			b = true;
			redirections.push_back(input[i]);
		}
		else throw Exception("redirection fault. ");
	}
}

unique_ptr<Command> TokenProcessor::createCommand() {
	if (command == commands[ECHO]) {
		unique_ptr<Echo> echo = make_unique<Echo>(attributes, redirections);
		return echo;
	}
	else if (command == commands[PROMPT]) {
		unique_ptr<Prompt> p = make_unique<Prompt>(attributes, redirections);
		return p;
	}
	else if (command == commands[TIME]) {
		unique_ptr<Time> time = make_unique<Time>(attributes, redirections);
		return time;
	}
	else if (command == commands[DATE]) {
		unique_ptr<Date> date = make_unique<Date>(attributes, redirections);
		return date;
	}
	else if (command == commands[TOUCH]) {
		unique_ptr<Touch> touch = make_unique<Touch>(attributes, redirections);
		return touch;
	}
	else if (command == commands[TRUNCATE]) {
		unique_ptr<Truncate> trunc = make_unique<Truncate>(attributes, redirections);
		return trunc;
	}
	else if (command == commands[RM_]) {
		unique_ptr<RM> rm = make_unique<RM>(attributes, redirections);
		return rm;
	}
	else if (command == commands[WC_]) {
		unique_ptr<WC> wc = make_unique<WC>(attributes, redirections);
		return wc;
	}
	else if (command == commands[TR_]) { 
		unique_ptr<TR> tr = make_unique<TR>(attributes, redirections);
		return tr;
	}
	else if (command == commands[HEAD]) {
		unique_ptr<Head> head = make_unique<Head>(attributes, redirections);
		return head;
	}
	else if (command == commands[BATCH]) {
		unique_ptr<Batch> batch = make_unique<Batch>(attributes, redirections);
		return batch;
	}
	else {
		throw UnknownCommandException(command);
	}
}

const string TokenProcessor::commands[commandsNumber] = { "echo", "prompt", "time",	"date", "touch", "truncate",
	"rm", "wc", "tr", "head", "batch" };
