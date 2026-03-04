#include "Parser.h"
#include "Exception.h"

Parser::Parser() {}

void Parser::cutLine(string& line) { 
    int start = 0;
    skipSpaces(line, start);
    line = line.substr(start, static_cast<size_t>(maxLineLength - start));
}

void Parser::skipSpaces(string line, int& cnt) {
    while (cnt < (int)line.size() && isspace((unsigned char)line[cnt])) cnt++;
}

void Parser::catchUntilSpace(string line, string& text, int& cnt) {
    while (cnt < (int)line.size() && !isspace((unsigned char)line[cnt])) {
        text += line[cnt++];
    }
}

void Parser::catchQM(string line, string& text, int& cnt) {
    text += line[cnt++];
    while (cnt < (int)line.size()) {
        if (line[cnt] == '"') {
            text += line[cnt++];
            return;
        }
        text += line[cnt++];
    }

    throw SyntaxException::qmNotClosed();    
}

void Parser::catchRedirection(string line, string& text, int& cnt) {
    text += line[cnt++];
    skipSpaces(line, cnt);
    catchUntilSpace(line, text, cnt);
}

void Parser::catchRedirectionAppend(string line, string& text, int& cnt) {
    text += line[cnt++];
    text += line[cnt++];
    skipSpaces(line, cnt);
    catchUntilSpace(line, text, cnt);
}

vector<Token> Parser::parseLine(string& line) {
    vector<Token> parsed;
    int cnt = 0;
    while (cnt < line.size()) {
        string text = "";
        skipSpaces(line, cnt);
        if (cnt >= line.size()) break;
        if (line[cnt] == '"') { // Argument with quotation marks 
            catchQM(line, text, cnt);
            parsed.push_back(Token(text, Token::ARGUMENT_QM));
            continue;
        }
        if (line[cnt] == '-') { // Option
            catchUntilSpace(line, text, cnt);
            parsed.push_back(Token(text, Token::OPTION));
            continue;
        }
        if (line[cnt] == '<') { // Input redirection
            catchRedirection(line, text, cnt);
            parsed.push_back(Token(text, Token::INPUT_REDIRECTION));
            continue;
        }
        if (line.substr(cnt, 2) == ">>") { // Output redirection
            catchRedirectionAppend(line, text, cnt);
            parsed.push_back(Token(text, Token::OUTPUT_REDIRECTION_APPEND));
            continue;
        }
        if (line[cnt] == '>') { // Output append redirection
            catchRedirection(line, text, cnt);
            parsed.push_back(Token(text, Token::OUTPUT_REDIRECTION));
            continue;
        }
        catchUntilSpace(line, text, cnt); // Command or file
        parsed.push_back(Token(text, Token::UNKNOWN));
    }
    return parsed;
}
