#include "includes.h"

Tokenizer::Tokenizer()
{
	implied = { "BRK", "RTI", "RTS", "PHP", "CLC", "PLP", "SEC", "PHA", "CLI",
		"PLA", "SEI", "DEY", "TYA", "TAY", "CLV", "INY", "CLD", "INY",
		"CLD", "INX", "SED", "TXA", "TXS", "TAX", "TSX", "DEX", "NOP" };

	// implied: ^\s*(\w+)\s*$
	implied_re = regex(R"(^\s*(\w+)\s*$)");
	
	relative = { "BPL", "BMI", "BVC", "BVS", "BCC", "BCS", "BNE", "BEQ" };

	// relative: OPC $BB
	// ^\s*(\w+)\s+\$(\d+).*\s*$
	relative_re = regex(R"((([A-Z]{3}) \$([0-9]{2})))");

	implied_b = begin(implied);
	implied_e = end(implied);

	relative_b = begin(relative);
	relative_e = end(relative);
}

Tokenizer::~Tokenizer()
{
	//dtor
}

TokenResult Tokenizer::tokenize(string& line) {
	TokenResult tr;
	smatch sm;

	if (regex_match(line, sm, implied_re)) {
		tr.instruction = sm[0];
		tr.address_mode = Implied;
	} else if (regex_match(line, sm, relative_re)) {
		auto pieces = split(line, ' ');
		tr.instruction = pieces[0];
		tr.address_mode = Relative;
		// tr.relative_byte = translate_hex(pieces[1].substr(1, string::npos));
		tr.relative_byte = translate_hex(pieces[1]);
	} else {
		throw UnknownInstruction("unhandled addressing mode for instruction " + tr.instruction);
	}

	return tr;
}

uint8_t Tokenizer::translate_hex(string& hexstr) {
	return (uint8_t) strtol(hexstr.c_str(), nullptr, 16);
}

vector<string> Tokenizer::split(string& line, char delim) {
	vector<string> parts;

	stringstream ss(line);
	string part;

	while (getline(ss, part, ' ')) {
		parts.push_back(part);
	}

	return parts;
}
