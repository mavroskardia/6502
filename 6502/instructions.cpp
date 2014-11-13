#include "includes.h"

void Instruction::operator() (CPU& cpu, Memory& mem) {
	increment_pc(cpu); // standard increment of the PC for this instruction
	execute(cpu, mem); // actual logic of instruction
}

namespace Impl {
	void BRK::execute(CPU& cpu, Memory& mem) {		
		dbgout("BRK: " << cpu.str() << endl);
	}

	void RTI::execute(CPU& cpu, Memory& mem) {
		dbgout("RTI: " << cpu.str() << endl);
	}

	void RTS::execute(CPU& cpu, Memory& mem) {
		// return from subroutine. takes the address from the next two bytes on the stack
		uint8_t hi = mem.pop_stack(cpu.sp);
		uint8_t lo = mem.pop_stack(cpu.sp);
		cpu.pc = (hi << 8 | lo) + 0x01;
	}

	void PHP::execute(CPU& cpu, Memory& mem) {
		// put the status register onto the stack
		mem.push_stack(cpu.sp, cpu.p);
	}

	void PLP::execute(CPU& cpu, Memory& mem) {
		// pull the status register off the stack
		cpu.p = mem.pop_stack(cpu.sp);
	}

	void CLC::execute(CPU& cpu, Memory& mem) {
		// clear the carry flag
		cpu.p_c(false);
	}

	void SEC::execute(CPU& cpu, Memory& mem) {
		// set the carry flag
		cpu.p_c(true);
	}

	void PHA::execute(CPU& cpu, Memory& mem) {
		// push A on to stack
		mem.push_stack(cpu.sp, cpu.acc);
	}

	void CLI::execute(CPU& cpu, Memory& mem) {
		// clear the interrupt bit of the status register
		cpu.p_i(false);
	}

	void PLA::execute(CPU& cpu, Memory& mem) {
		// pop the stack into the accumulator
		cpu.acc = mem.pop_stack(cpu.sp);
	}

	void SEI::execute(CPU& cpu, Memory& mem) {
		// set the interrupt flag of the status register
		cpu.p_i(true);
	}

	void DEY::execute(CPU& cpu, Memory& mem) {
		// decrement y by one, set appropriate flags		
		cpu.p_z(--cpu.y == 0);
		cpu.p_n(cpu.y > 0x7f);
	}

	void TYA::execute(CPU& cpu, Memory& mem) {
		// transfer y to the accumulator
		cpu.acc = cpu.y;
		cpu.p_z(cpu.acc == 0);
		cpu.p_n(cpu.acc > 0x7f);
	}
	
	void TAY::execute(CPU& cpu, Memory& mem) {
		// transfer accumulator to y
		cpu.y = cpu.acc;
		cpu.p_z(cpu.y == 0);
		cpu.p_n(cpu.y > 0x7f);
	}

	void CLV::execute(CPU& cpu, Memory& mem) {
		// clear the overflow flag
		cpu.p_v(false);
	}

	void INY::execute(CPU& cpu, Memory& mem) {
		// increment y
		cpu.p_z(++cpu.y == 0);
		cpu.p_n(cpu.y > 0x7f);
	}

	void CLD::execute(CPU& cpu, Memory& mem) {
		// clear decimal bit
		cpu.p_d(false);
	}

	void INX::execute(CPU& cpu, Memory& mem) {
		// increment X
		cpu.p_z(++cpu.x == 0);
		cpu.p_n(cpu.x > 0x7f);
	}

	void SED::execute(CPU& cpu, Memory& mem) {
		// sed decimal bit
		cpu.p_d(true);
	}

	void TXA::execute(CPU& cpu, Memory& mem) {
		// transfer x to the accumulator
		cpu.acc = cpu.x;
		cpu.p_z(cpu.acc == 0);
		cpu.p_n(cpu.acc > 0x7f);
	}

	void TXS::execute(CPU& cpu, Memory& mem) {
		// transfer x to the stack pointer
		cpu.sp = cpu.x;
	}

	void TAX::execute(CPU& cpu, Memory& mem) {
		// transfer the accumulator to x
		cpu.x = cpu.acc;
		cpu.p_n(cpu.x > 0x7f);
		cpu.p_z(cpu.x == 0);
	}

	void TSX::execute(CPU& cpu, Memory& mem) {
		// transfer stack pointer to x (TODO: check for invalid stack pointer values?)
		cpu.x = cpu.sp;
	}

	void DEX::execute(CPU& cpu, Memory& mem) {
		// decrement x by one		
		cpu.p_n(--cpu.x > 0x7f);
		cpu.p_z(cpu.x == 0);
	}

	void NOP::execute(CPU& cpu, Memory& mem) {}
}

namespace Rel {
	
	void BPL::execute(CPU& cpu, Memory& mem) {
		int8_t rel = mem[cpu.pc - 1]; // make sure it's an int8_t so that the range is interpreted as -128 to 127
		if (!cpu.p_n()) cpu.pc += rel;
	}

	void BMI::execute(CPU& cpu, Memory& mem) {
		int8_t rel = mem[cpu.pc - 1];
		if (cpu.p_n()) cpu.pc += rel;
	}

	void BVC::execute(CPU& cpu, Memory& mem) {
		int8_t rel = mem[cpu.pc - 1];
		if (!cpu.p_v()) cpu.pc += rel;
	}

	void BVS::execute(CPU& cpu, Memory& mem) {
		int8_t rel = mem[cpu.pc - 1];
		if (cpu.p_v()) cpu.pc += rel;
	}

	void BCC::execute(CPU& cpu, Memory& mem) {
		int8_t rel = mem[cpu.pc - 1];
		if (cpu.p_c()) cpu.pc += rel;
	}

	void BCS::execute(CPU& cpu, Memory& mem) {
		int8_t rel = mem[cpu.pc - 1];
		if (!cpu.p_c()) cpu.pc += rel;
	}

	void BNE::execute(CPU& cpu, Memory& mem) {
		int8_t rel = mem[cpu.pc - 1];
		if (!cpu.p_z()) cpu.pc += rel;
	}

	void BEQ::execute(CPU& cpu, Memory& mem) {
		int8_t rel = mem[cpu.pc - 1];
		if (cpu.p_z()) cpu.pc += rel;
	}

}

namespace Absolute {

	void JSR::execute(CPU& cpu, Memory& mem) {
		auto topush = cpu.pc - 1;
		uint8_t lo = topush & 0x00ff;
		uint8_t hi = (topush & 0xff00) >> 8;
		mem.push_stack(cpu.sp, lo);
		mem.push_stack(cpu.sp, hi);
		cpu.pc = (mem[cpu.pc - 1] << 8) | mem[cpu.pc - 2];
	}

	void BIT::execute(CPU& cpu, Memory& mem) {
		auto pointer = (mem[cpu.pc - 1] << 8) | mem[cpu.pc - 2];
		auto val = mem[pointer];
		auto result = cpu.acc & val;

		cpu.p_n(result > 0x7f);
		cpu.p_v((result & 0x20) > 0);
		cpu.p_z(result == 0);
	}

	void JMP::execute(CPU& cpu, Memory& mem) {
		auto pointer = (mem[cpu.pc - 1] << 8) | mem[cpu.pc - 2];
		cpu.pc = pointer;
	}

	void STY::execute(CPU& cpu, Memory& mem) {
		auto pointer = (mem[cpu.pc - 1] << 8) | mem[cpu.pc - 2];
		mem[pointer] = cpu.y;
	}

	void LDY::execute(CPU& cpu, Memory& mem) {
		auto pointer = (mem[cpu.pc - 1] << 8) | mem[cpu.pc - 2];
		cpu.y = mem[pointer];
	}

	void CPY::execute(CPU& cpu, Memory& mem) {
		auto pointer = (mem[cpu.pc - 1] << 8) | mem[cpu.pc - 2];
		uint8_t result = cpu.y - mem[pointer];
		cpu.p_n(result > 0x7f);
		cpu.p_z(result == 0);
		cpu.p_c(cpu.y >= mem[pointer]);
	}

	void CPX::execute(CPU& cpu, Memory& mem) {
		auto pointer = (mem[cpu.pc - 1] << 8) | mem[cpu.pc - 2];
		uint8_t result = cpu.x - mem[pointer];
		cpu.p_n(result > 0x7f);
		cpu.p_z(result == 0);
		cpu.p_c(cpu.x >= mem[pointer]);
	}

	void ORA::execute(CPU& cpu, Memory& mem) {
		auto pointer = (mem[cpu.pc - 1] << 8) | mem[cpu.pc - 2];
		cpu.acc |= mem[pointer];
		cpu.p_n(cpu.acc > 0x7f);
		cpu.p_z(cpu.acc == 0);
	}

	void AND::execute(CPU& cpu, Memory& mem) {
		auto pointer = (mem[cpu.pc - 1] << 8) | mem[cpu.pc - 2];
		cpu.acc &= mem[pointer];
		cpu.p_n(cpu.acc > 0x7f);
		cpu.p_z(cpu.acc == 0);
	}

	void EOR::execute(CPU& cpu, Memory& mem) {
		auto pointer = (mem[cpu.pc - 1] << 8) | mem[cpu.pc - 2];
		cpu.acc ^= mem[pointer];
		cpu.p_n(cpu.acc > 0x7f);
		cpu.p_z(cpu.acc == 0);
	}

}

namespace AbsoluteX {

}

namespace AbsoluteY {

}