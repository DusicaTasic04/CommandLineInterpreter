#ifndef READER_H
#define READER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Abstract class which is responsible for reading from an
// input file or console. 

class Reader {
public:

	// Virtual. Returns the line which was last read.
	virtual string getLine();

	// Virtual. Reads an input line.
	virtual void readLine() = 0;

	// Virtual. Reads from cin or file until it meets an EOF character.
	virtual string readUntilEOF() = 0;

	// Virtual. Checks for EOF.
	virtual bool isEnd() = 0;

protected:

	string line;

private:

};

// Inherits the Reader class. Reads from the console input.

class CReader : public Reader {
public:
	// Constructor.
	CReader();

	// Virtual. Reads an input line from console input.
	virtual void readLine() override;

	// Virtual. Checks for EOF.
	virtual bool isEnd() override;

	// Virtual. Reads from cin until it meets an EOF character.
	string readUntilEOF() override;

protected:

private:

};

class FReader : public Reader {
public:

	// Constructor.
	FReader(string fileName);

	// Virtual. Reads an input line from a file input.
	virtual void readLine() override;

	// Virtual. Checks for EOF.
	virtual bool isEnd() override; 

	// Virtual. Reads from a file until it meets an EOF character.
	string readUntilEOF();

	// Destructor. Frees memory and closes the file.
	~FReader();

protected:

private:
	ifstream* fileInput;
};

#endif