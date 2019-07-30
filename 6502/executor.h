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
	std::map<uint8_t, Instruction*> instructions = {
		// implied
		{ 0x00, new Impl::BRK() }, { 0x40, new Impl::RTI() }, { 0x60, new Impl::RTS() },
		{ 0x8a, new Impl::TXA() }, { 0x9a, new Impl::TXS() }, { 0xaa, new Impl::TAX() },
		{ 0xba, new Impl::TSX() }, { 0xca, new Impl::DEX() }, { 0xea, new Impl::NOP() },
		{ 0x08, new Impl::PHP() }, { 0x18, new Impl::CLC() }, { 0x28, new Impl::PLP() },
		{ 0x38, new Impl::SEC() }, { 0x48, new Impl::PHA() }, { 0x58, new Impl::CLI() },
		{ 0x68, new Impl::PLA() }, { 0x78, new Impl::SEI() }, { 0x88, new Impl::DEY() },
		{ 0x98, new Impl::TYA() }, { 0xa8, new Impl::TAY() }, { 0xb8, new Impl::CLV() },
		{ 0xc8, new Impl::INY() }, { 0xd8, new Impl::CLD() }, { 0xe8, new Impl::INX() },
		{ 0xf8, new Impl::SED() },
		// relative
		{ 0x10, new Rel::BPL() }, { 0x30, new Rel::BMI() }, { 0x50, new Rel::BVC() },
		{ 0x70, new Rel::BVS() }, { 0x90, new Rel::BCC() }, { 0xb0, new Rel::BCS() },
		{ 0xd0, new Rel::BNE() }, { 0xf0, new Rel::BEQ() },
		// absolute
		{ 0x20, new Absolute::JSR() }, { 0x2c, new Absolute::BIT() }, { 0x4c, new Absolute::JMP() },
		{ 0x8c, new Absolute::STY() }, { 0xac, new Absolute::LDY() }, { 0xcc, new Absolute::CPY() },
		{ 0xec, new Absolute::CPX() }, { 0x0d, new Absolute::ORA() }, { 0x2d, new Absolute::AND() },
		{ 0x4d, new Absolute::EOR() }
	};
};

#endif