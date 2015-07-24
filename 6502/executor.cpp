#include "includes.h"

Executor::Executor() {
	// 0x*1 implied
	instructions[0x60] = new Impl::BRK();
	instructions[0x40] = new Impl::RTI();
	instructions[0x60] = new Impl::RTS();

	// 0x*a implied
	instructions[0x8a] = new Impl::TXA();
	instructions[0x9a] = new Impl::TXS();
	instructions[0xaa] = new Impl::TAX();
	instructions[0xba] = new Impl::TSX();
	instructions[0xca] = new Impl::DEX();
	instructions[0xea] = new Impl::NOP();

	// 0x*8 implied
	instructions[0x08] = new Impl::PHP();
	instructions[0x18] = new Impl::CLC();
	instructions[0x28] = new Impl::PLP();
	instructions[0x38] = new Impl::SEC();
	instructions[0x48] = new Impl::PHA();
	instructions[0x58] = new Impl::CLI();
	instructions[0x68] = new Impl::PLA();
	instructions[0x78] = new Impl::SEI();
	instructions[0x88] = new Impl::DEY();
	instructions[0x98] = new Impl::TYA();
	instructions[0xa8] = new Impl::TAY();
	instructions[0xb8] = new Impl::CLV();
	instructions[0xc8] = new Impl::INY();
	instructions[0xd8] = new Impl::CLD();
	instructions[0xe8] = new Impl::INX();
	instructions[0xf8] = new Impl::SED();	

	// relative
	instructions[0x10] = new Rel::BPL();
	instructions[0x30] = new Rel::BMI();
	instructions[0x50] = new Rel::BVC();
	instructions[0x70] = new Rel::BVS();
	instructions[0x90] = new Rel::BCC();
	instructions[0xb0] = new Rel::BCS();
	instructions[0xd0] = new Rel::BNE();
	instructions[0xf0] = new Rel::BEQ();

	// absolute 
	instructions[0x20] = new Absolute::JSR();

	instructions[0x2c] = new Absolute::BIT();
	instructions[0x4c] = new Absolute::JMP();
	instructions[0x8c] = new Absolute::STY();
	instructions[0xac] = new Absolute::LDY();
	instructions[0xcc] = new Absolute::CPY();
	instructions[0xec] = new Absolute::CPX();

	instructions[0x0d] = new Absolute::ORA();	
	instructions[0x2d] = new Absolute::AND();
	instructions[0x4d] = new Absolute::EOR();

	/*
	instructions[0x6d] = new Absolute::ADC();
	instructions[0x8d] = new Absolute::STA();
	instructions[0xad] = new Absolute::LDA();
	instructions[0xcd] = new Absolute::CMP();
	instructions[0xed] = new Absolute::SBC();

	instructions[0x0e] = new Absolute::ASL();
	instructions[0x2e] = new Absolute::ROL();
	instructions[0x4e] = new Absolute::LSR();
	instructions[0x6e] = new Absolute::ROR();
	instructions[0x8e] = new Absolute::STX();
	instructions[0xae] = new Absolute::LDX();
	instructions[0xce] = new Absolute::DEC();
	instructions[0xee] = new Absolute::INC();
	*/

	// absolute X

	// absolute Y



}

Instruction* Executor::instruction(const uint8_t opcode) {
	return instructions[opcode];
}

bool Executor::load(string filename) {
	ifstream file(filename, ios::in | ios::binary | ios::ate);
	int length;
	
	dbgout("Reading file " << filename << "...");

	if (file.is_open()) {
		length = (int)file.tellg();
		file.seekg(0, ios::beg);
		program = vector<uint8_t>(length, 0);

		file.read((char*)&program[0], length);
		file.close();
	}
	else {
		dbgout("Failed to open file with name " << filename << endl);
		return false;
	}

	dbgout("done." << endl);
	dbgout("Filesize is " << program.size() << " bytes." << endl);

	return length == program.size();
}

bool Executor::bootstrap() {	
	// standard starting execution location is 0x8000:
	memory.memory[0xfffc] = 0x00;
	memory.memory[0xfffd] = 0x80;
	
	// load program into memory
	auto mem_itr = begin(memory.memory);
	advance(mem_itr, 0x8000);
	copy(begin(program), end(program), mem_itr);

	cpu.p_i(true);
	cpu.pc = (memory[0xfffd] << 8) | memory[0xfffc];

	return true;
}

bool Executor::run() {
	running = true;
	auto sleep_time = chrono::milliseconds(1);	

	if (!bootstrap()) {
		cerr << "Failed to bootstrap system before execution, cannot continue." << endl;
		return false;
	}

	while (running) {
		this_thread::sleep_for(sleep_time);
		auto& istr = (*instructions[memory[cpu.pc]]);
		dbgout(istr.str() << endl);
		istr(cpu, memory);		
	}

	return true;
}
