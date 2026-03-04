#include "Exception.h"

Exception::Exception(const string& msg) : message(msg) {}

const char* Exception::what() const noexcept {
    return message.c_str();
}

UnknownCommandException::UnknownCommandException(string command) : Exception("unknown command \"" + command + "\". ") {}

SyntaxException::SyntaxException(const string& msg) : Exception(msg) { }

SyntaxException SyntaxException::qmNotClosed() {
    return SyntaxException("closing quotation mark not found. ");
}

SyntaxException SyntaxException::qmMissing() {
    return SyntaxException("argument must be under quotation marks. ");
}

SyntaxException SyntaxException::invalidPipeUsage() {
    return SyntaxException("invalid pipe usage - command missing. ");
}

RedirectionException::RedirectionException(const string& msg) : Exception(msg) { }

RedirectionException RedirectionException::unsupported() {
    return RedirectionException("this command does not support redirection. ");
}

RedirectionException RedirectionException::unsupportedInput() {
    return RedirectionException("this command does not support input redirection. ");
}

RedirectionException RedirectionException::unsupportedOutput() {
    return RedirectionException("this command does not support output redirection. ");
}

RedirectionException RedirectionException::duplicateInput() {
    return RedirectionException("input redirection is defined more than once. ");
}

RedirectionException RedirectionException::duplicateOutput() {
    return RedirectionException("output redirection is defined more than once. ");
}

RedirectionException RedirectionException::missingArgument() {
    return RedirectionException("arguments missing. ");
}

RedirectionException RedirectionException::excessiveArguments() {
    return RedirectionException("too much arguments given. ");
}

RedirectionException RedirectionException::unexpectedArgument() {
    return RedirectionException("this command does not have any arguments. ");
}

