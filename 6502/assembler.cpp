#include "includes.h"

Assembler::Assembler() {
	instruction_set = map<string, unsigned char> {
			{ "BRK", 0x00 },
			{ "BPL", 0x10 }
	};
}

Assembler::Assembler(const char* filename) {
	Assembler();
	readlines(filename);
}

void Assembler::readlines(const char* filename) {
	string line;
	ifstream f(filename);

	if (!f.is_open()) {
		throw GeneralException("Failed to read file");
	}

	while (getline(f, line))
		lines.push_back(line);

	f.close();
}

vector<unsigned char> Assembler::decodeline(string line) {
	vector<unsigned char> result;

	auto tr = tokenizer.tokenize(line);
	auto translation = translate_instruction(tr.instruction);

	result.push_back(translation);

	switch (tr.address_mode) {
	case Implied:
		break;
	case Relative:
		result.push_back(cpu.pc + tr.relative_byte);
		break;
	default:
		throw UnknownInstruction("Unknown addressing mode!");
	}

	return result;
}

vector<unsigned char> Assembler::decodeline() {
	return decodeline(lines[line_number++]);
}

unsigned char Assembler::translate_instruction(string instruction) {

	if (!instruction_set.count(instruction)) {
		throw UnknownInstruction(instruction);
	}

	return instruction_set[instruction];
}
