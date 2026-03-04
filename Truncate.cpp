#include "Truncate.h"

#include <fstream>
#include <system_error>

Truncate::Truncate(vector<Token> attributes, vector<Token> redirections) : 
    CommandFileManager() {
    setRedirections(redirections);
    setAttributes(attributes);

    ifstream fileCheck(filename);
    if (!fileCheck || !fileCheck.is_open()) {
        throw system_error(errno, generic_category(), filename);
    }
    fileCheck.close();
}

void Truncate::execute() {
    std::ofstream file(filename, std::ios::out);
    if (file.is_open()) {
        file << ""; 
        file.close();
    }
    else {
        throw system_error(errno, generic_category(), filename);
    }
}
