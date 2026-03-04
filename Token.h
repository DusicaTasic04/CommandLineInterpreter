#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "Exception.h"

using namespace std;

// Represents a string parameter along with its identified type.
// Note: The type may be incorrectly assigned,
// which should be ignored later in processing.
class Token {
public:
	// Constructs a Token with the given string and type.
	inline Token(const string& value = "", int type = 0) : value(value) { setType(type); }

	enum EToken {
		UNKNOWN, ARGUMENT_QM, OPTION, INPUT_REDIRECTION, OUTPUT_REDIRECTION,
		OUTPUT_REDIRECTION_APPEND
	};

	// Returns the type of this token.
	inline int getType() const { return this->type; }
	
	// If passed corectly, sets the type of a token.
	void setType(int type);

	// Returns the token as a string.
	inline string getValue() { return this->value; }

private:
	string value;
	int type;
};

inline void Token::setType(int type) {
	if (type < UNKNOWN || type > OUTPUT_REDIRECTION_APPEND)
		throw Exception("parameter type out of bounds. ");
	this->type = type;
}

#endif // !TOKEN_H