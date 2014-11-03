#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "includes.h"

using namespace std;

enum Modes {
	Implied, Relative
};

struct TokenResult {
	string instruction;
	Modes address_mode;
	union {
		int8_t relative_byte; // must be signed since you can have negative offsets
	};
};

class Tokenizer
{
public:
	Tokenizer();
	~Tokenizer();

	TokenResult tokenize(string& line);

protected:
private:
	vector<string> split(string& line, char delim);
	uint8_t translate_hex(string& hexstr);
	
	vector<string> implied, relative;
	vector<string>::iterator implied_b, implied_e, relative_b, relative_e;

	regex implied_re, relative_re;
};

#endif // TOKENIZER_H
