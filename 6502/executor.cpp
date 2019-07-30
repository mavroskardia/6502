#include "includes.h"

Executor::Executor() {

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

Instruction* Executor::instruction(uint8_t opcode) {
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
