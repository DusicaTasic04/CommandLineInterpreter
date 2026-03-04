#include "Touch.h"

#include <fstream>
#include <system_error>

Touch::Touch(vector<Token> attributes, vector<Token> redirections) : 
    CommandFileManager() {
    setRedirections(redirections);
    setAttributes(attributes);

    FileException::fileExists(filename);
}

void Touch::execute() {
    ofstream newFile(filename);
    if (!newFile) {
        throw system_error(errno, generic_category(), filename);
    }
    newFile.close();
}
