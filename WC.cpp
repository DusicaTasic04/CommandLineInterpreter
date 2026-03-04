#include "WC.h"

WC::WC(vector<Token> attributes, vector<Token> redirections) : 
    CommandOptionArgument(), counter(0) { 
    setRedirections(redirections);
    setAttributes(attributes);
}

void WC::executeCommandOneArgument() {
    if (option == "-c") {
        this->charCount();
    }
    else if (option == "-w") {
        this->wordCount();
    }
    else
        throw Exception("unknown option: " + option);
    output = to_string(counter);
}

void WC::charCount() {
    counter = static_cast<int>(argument->size());
}

void WC::wordCount() {
    int i = 0;
    while (i < argument->size()) { 
        while (i < (int)argument->size() && isspace((unsigned char)(*argument)[i])) i++;
        if (i < (int)argument->size() && !isspace((unsigned char)(*argument)[i])) counter++;
        while (i < (int)argument->size() && !isspace((unsigned char)(*argument)[i])) i++;
    }
}
