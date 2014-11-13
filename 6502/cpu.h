#ifndef CPU_H
#define CPU_H

class CPU {
public:
	uint16_t pc = 0;	// 16-bit program counter
	uint8_t sp = 0;		// 8-bit stack pointer
	uint8_t acc = 0;	// 8-bit accumulator
	uint8_t x = 0;		// 8-bit x register
	uint8_t y = 0;		// 8-bit y register
	uint8_t p = 0;		// 8-bit status register

	bool p_n();		// negative bit	
	bool p_v();		// overflow bit	
	bool p_b();		// break bit
	bool p_d();		// decimal bit	
	bool p_i();		// interrupt bit	
	bool p_z();		// zero bit	
	bool p_c();		// carry bit

	void p_n(bool);
	void p_v(bool);
	void p_b(bool);
	void p_d(bool);
	void p_i(bool);
	void p_z(bool);
	void p_c(bool);

	std::string str();
};

#endif // CPU_H
