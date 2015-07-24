#ifndef _6502EXCEPTIONS_H
#define _6502EXCEPTIONS_H

#include "includes.h"

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

class UnknownInstruction : public std::exception
{
public:
	UnknownInstruction(std::string instruction) : instruction(instruction) {}
	const char* what() const NOEXCEPT { return instruction.c_str(); }
private:
	std::string instruction;
};

class GeneralException : public std::exception {
public:
	GeneralException(std::string message) : message(message) {};
	const char* what() const NOEXCEPT { return message.c_str(); }
protected:
	std::string message;
};

class SyntaxException : public GeneralException {
public:
	SyntaxException(std::string message) : GeneralException(message) {};
};

#endif // _6502EXCEPTIONS_H
