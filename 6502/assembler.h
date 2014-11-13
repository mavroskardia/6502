#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "includes.h"

class Assembler {
public:
	Assembler();
	Assembler(const char* filename);

	vector<unsigned char> decodeline();
	vector<unsigned char> decodeline(string line);

	unsigned int current_line_number() { return line_number; }
	bool eof() { return line_number >= lines.size(); };

private:
	void readlines(const char* filename);
	unsigned char translate_instruction(string instruction);

	vector<string> lines;
	map<string, unsigned char> instruction_set;
	Tokenizer tokenizer;
	unsigned int line_number = 0;

	CPU cpu;
};

#endif // ASSEMBLER_H
