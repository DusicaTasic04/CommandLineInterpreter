#include "Interpreter.h"

int main() {

	Interpreter* interpreter = Interpreter::Instance();
	while (true) {
		interpreter->process();
	}
	return 0;
	
}