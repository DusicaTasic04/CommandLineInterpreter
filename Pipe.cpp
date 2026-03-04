#include "Pipe.h"
#include "Parser.h"
#include "Exception.h"

#include <sstream>

Pipe::Pipe(char delimiter = '|') : delimiter(delimiter) { }

void Pipe::setCommand(string segment) {
	Parser::cutLine(segment);
	if (segment == "") throw SyntaxException::invalidPipeUsage();

	tokenProcessor.setElements(Parser::parseLine(segment));
	unique_ptr<Command> command = tokenProcessor.createCommand();
	commands.push_back(move(command));
}

void Pipe::splitPipeline(string line) {
	ostringstream oss;
	commands.clear();
	int qmCnt = 0; // Quotation marks counter
	int i = 0;
	string segment = "";
	while (i < line.size()) {
		if (line[i] == '"') {
			qmCnt++;
			segment += line[i++];
		}
		else if (line[i] == '|' && !(qmCnt % 2)) {
			setCommand(segment);

			segment = "";
			i++;
		}
		else
			segment += line[i++];
	}
	setCommand(segment);
}

void Pipe::processLine() { 
	ostringstream* oss = new ostringstream;
	int excptCnt = 0;
	for (auto command = commands.begin(); command != commands.end(); command++) {
		excptCnt++;
		try {
			if (!(command == commands.begin())) {
				unique_ptr<Command>& c = *command;
				CommandOneArgument* carg = dynamic_cast<CommandOneArgument*>(c.get());
				if (!carg) throw RedirectionException::unsupported();
				carg->setArgument(oss->str()); // Command is not first in this case, gets input from oss
				oss->str("");
				oss->clear();
			}

			if (!(next(command) == commands.end()))
				(*command)->setOutputTarget(oss);
			
			(*command)->execute();
			(*command)->printOutput();
		}
		catch (exception& e) {
			throw Exception((string)"Command[" + to_string(excptCnt) + (string)"]: " + e.what());
			break;
		}
	}
}
