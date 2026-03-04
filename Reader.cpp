#include "Reader.h"

string Reader::getLine() {
	return line;
}

CReader::CReader() { }

void CReader::readLine() {
	getline(cin, line);
	if (cin.fail()) {
		cin.ignore();
		cin.clear();
	}
}

bool CReader::isEnd() {
	return cin.eof();
}

string CReader::readUntilEOF() {
	string content, s;
	while (getline(cin, s)) {
		content += s + "\n";
	}
	cin.ignore();
	cin.clear();
	return content;
}

FReader::FReader(string fileName) : fileInput(new ifstream(fileName)) {
	if (!fileInput->is_open()) { 
		throw system_error(errno, generic_category(), fileName);
		delete fileInput;
		fileInput = nullptr;
	}
}

void FReader::readLine() {
	if (fileInput && !isEnd()) {
		getline(*fileInput, line);
	}
}

bool FReader::isEnd() {
	return !fileInput || fileInput->eof();
}

string FReader::readUntilEOF() {
	string content;
	while (true) {
		int ch = fileInput->get();
		if (ch == EOF) break;
		content += ch;
	}
	return content;
}

FReader::~FReader() {
	if (fileInput) {
		fileInput->close();
		delete fileInput;
	}
}
