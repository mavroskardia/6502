#ifndef _MEMORY_H
#define _MEMORY_H

#include "includes.h"

class Memory {
public:
	Memory();
	~Memory();

	uint8_t& operator[](const int index);
	
	bool push_stack(uint8_t& sp, uint8_t v);
	uint8_t pop_stack(uint8_t& sp);

	std::vector<uint8_t> memory;	
};

#endif