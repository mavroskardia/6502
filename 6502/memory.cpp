#include "includes.h"

Memory::Memory() {
	memory.clear();
	memory.resize(0xffff, 0);
}

Memory::~Memory() {}

uint8_t& Memory::operator[] (const int index) {
	return memory[index];
}


// stack ops:
// stack is top-down, so first value on the stack goes to 0x1ff, then 0x1fe, etc.
// each push points the SP to the next available stack location, so it will start at 0 (0x1ff - 0),
// then to 1, (0x1ff - 1 = 0x1fe), etc.

bool Memory::push_stack(uint8_t& sp, uint8_t value) {
	memory[0x1ff - sp++] = value;
	return true;
}

uint8_t Memory::pop_stack(uint8_t& sp) {
	uint8_t val = memory[0x1ff - --sp];
	return val;
}
