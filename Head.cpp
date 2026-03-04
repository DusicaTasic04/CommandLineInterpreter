#include "Head.h"
#include <regex>

Head::Head(vector<Token> attributes, vector<Token> redirections) : 
	CommandOptionArgument() { 
	setRedirections(redirections);
	setAttributes(attributes);
}

void Head::executeCommandOneArgument() {

	const string& arg = *argument;

	int count;
	if (regex_match(option, regex(R"(-n\d{1,5})")))
		count = getCount();
	else
		throw Exception("option was not entered in a good format. ");
	int from = 0, n = 0;
	for (int i = 0; i < arg.size(); i++) {
		if (arg[i] == '\n') {
			if (n == count) break;
			output += arg.substr(from, static_cast<size_t>(i) - from + 1);
			n++;			
			from = i + 1;
		}
	}
	if (n < count) 
		output += arg.substr(from, arg.size() - from + 1);
	if (output[output.size() - 1] != '\n') output += '\n';
}

void Head::printOutput() const {
	if (!outputTarget) (cout) << output;
	else (*outputTarget) << output << flush;
}

int Head::getCount() {
	return atoi(option.substr(2, option.size() - 2).c_str());
}
