#include "Exception.h"
#include <fstream>

FileException::FileException(const string& msg) : Exception(msg) { }

void FileException::checkFileAccessibility(string filename, ios::openmode mode) {
    fstream check(filename, mode);
    if (!check.is_open()) 
        throw system_error(errno, generic_category(), filename);
    check.close();
}

void FileException::fileExists(string filename) {
    ifstream fileCheck(filename);
    if (fileCheck.is_open()) {
        throw FileException(filename + " already exists.");
    }
    fileCheck.close();
}
