#include "Exception.h"

LexicalException::LexicalException(const string& msg) : Exception(msg) { }

const std::set<char> LexicalException::forbiddenChars = {
    '\/', ':', '*', '?'
};

void LexicalException::checkLexicography(string line) {
    bool forbiddenFound = false;
    string msg;
    int qmCnt = 0;
    for (int i = 0; i < line.size(); i++) {
        if (forbiddenChars.find(line[i]) != forbiddenChars.end() && !(qmCnt % 2)) {
            forbiddenFound = true;
            msg += "^";
        }
        else {
            if (line[i] == '"') qmCnt++;
            if (line[i] == '\t') msg += '\t';
            else msg += " ";
        }
    }

    if (forbiddenFound) {
        msg = "unexpected characters: \n" + line + "\n" + msg;
        throw LexicalException(msg);
    }
}