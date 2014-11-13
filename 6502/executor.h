#ifndef _EXECUTOR_H
#define _EXECUTOR_H

#include "includes.h"

class Executor {
public:
	Executor();

	bool load(std::string filename);
	bool run();
	bool bootstrap();
	Instruction* instruction(const uint8_t opcode);

private:
	bool running;
	
	CPU cpu;
	Memory memory; 
	
	std::vector<uint8_t> program;
	std::map<uint8_t, Instruction*> instructions;	
};

#endif