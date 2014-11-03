#include "includes.h"

string make_string(vector<unsigned char>&);

namespace impl {
	void test_brk(Instruction&, CPU&, Memory&);
	void test_rti(Instruction&, CPU&, Memory&);
	void test_rts(Instruction&, CPU&, Memory&);
	void test_php(Instruction&, CPU&, Memory&);
	void test_clc(Instruction&, CPU&, Memory&);
	void test_plp(Instruction&, CPU&, Memory&);
	void test_sec(Instruction&, CPU&, Memory&);
	void test_pha(Instruction&, CPU&, Memory&);
	void test_cli(Instruction&, CPU&, Memory&);
	void test_pla(Instruction&, CPU&, Memory&);
	void test_sei(Instruction&, CPU&, Memory&);
	void test_dey(Instruction&, CPU&, Memory&);
	void test_tya(Instruction&, CPU&, Memory&);
	void test_tay(Instruction&, CPU&, Memory&);
	void test_clv(Instruction&, CPU&, Memory&);
	void test_iny(Instruction&, CPU&, Memory&);
	void test_cld(Instruction&, CPU&, Memory&);
	void test_inx(Instruction&, CPU&, Memory&);
	void test_sed(Instruction&, CPU&, Memory&);

	void test_txa(Instruction&, CPU&, Memory&);
	void test_txs(Instruction&, CPU&, Memory&);
	void test_tax(Instruction&, CPU&, Memory&);
	void test_tsx(Instruction&, CPU&, Memory&);
	void test_dex(Instruction&, CPU&, Memory&);
	void test_nop(Instruction&, CPU&, Memory&);
}

namespace rel {
	void test_bpl(Instruction&, CPU&, Memory&);
	void test_bmi(Instruction&, CPU&, Memory&);
	void test_bvc(Instruction&, CPU&, Memory&);
	void test_bvs(Instruction&, CPU&, Memory&);
	void test_bcc(Instruction&, CPU&, Memory&);
	void test_bcs(Instruction&, CPU&, Memory&);
	void test_bne(Instruction&, CPU&, Memory&);
	void test_beq(Instruction&, CPU&, Memory&);
}

namespace abso {
	void test_jsr(Instruction&, CPU&, Memory&);

	void test_bit(Instruction&, CPU&, Memory&);
	void test_jmp(Instruction&, CPU&, Memory&);
	void test_sty(Instruction&, CPU&, Memory&);
	void test_ldy(Instruction&, CPU&, Memory&);
	void test_cpy(Instruction&, CPU&, Memory&);
	void test_cpx(Instruction&, CPU&, Memory&);

	void test_ora(Instruction&, CPU&, Memory&);
	void test_and(Instruction&, CPU&, Memory&);
	void test_eor(Instruction&, CPU&, Memory&);
	void test_adc(Instruction&, CPU&, Memory&);
	void test_sta(Instruction&, CPU&, Memory&);
	void test_lda(Instruction&, CPU&, Memory&);
	void test_cmp(Instruction&, CPU&, Memory&);
	void test_sbc(Instruction&, CPU&, Memory&);

	void test_asl(Instruction&, CPU&, Memory&);
	void test_rol(Instruction&, CPU&, Memory&);
	void test_lsr(Instruction&, CPU&, Memory&);
	void test_ror(Instruction&, CPU&, Memory&);
	void test_stx(Instruction&, CPU&, Memory&);
	void test_ldx(Instruction&, CPU&, Memory&);
	void test_dec(Instruction&, CPU&, Memory&);
	void test_inc(Instruction&, CPU&, Memory&);
}

void test_stack();
void do_memory_tests();

void do_implied_tests();
void do_relative_tests();
void do_absolute_tests();

void do_full_program_tests();

int do_tests() {
	do_memory_tests();
	do_implied_tests();
	do_relative_tests();
	do_absolute_tests();

	//do_full_program_tests();

	return 0;
}

void do_memory_tests() {
	test_stack();
}

void test_stack() {
	Memory m;
	uint8_t sp = 0xa0, ret = 0x0;

	m.push_stack(sp, 0xb1);
	m.push_stack(sp, 0xb2);
	assert(sp == 0xa2);
	assert(m[0x1ff - 0xa0] == 0xb1);
	assert(m[0x1ff - 0xa1] == 0xb2);

	ret = m.pop_stack(sp);
	assert(ret == 0xb2);
	assert(sp == 0xa1);
	assert(m[0x1ff - 0xa0] == 0xb1);
}

void do_implied_tests() {
	Executor e;
	CPU cpu;
	Memory mem;

	impl::test_brk(*e.instruction(0x00), cpu, mem);
	impl::test_rti(*e.instruction(0x40), cpu, mem);
	impl::test_rts(*e.instruction(0x60), cpu, mem);
	
	impl::test_txa(*e.instruction(0x8a), cpu, mem);
	impl::test_txs(*e.instruction(0x9a), cpu, mem);
	impl::test_tax(*e.instruction(0xaa), cpu, mem);
	impl::test_tsx(*e.instruction(0xba), cpu, mem);
	impl::test_dex(*e.instruction(0xca), cpu, mem);
	impl::test_nop(*e.instruction(0xea), cpu, mem);
	
	impl::test_php(*e.instruction(0x08), cpu, mem);
	impl::test_clc(*e.instruction(0x18), cpu, mem);
	impl::test_plp(*e.instruction(0x28), cpu, mem);
	impl::test_sec(*e.instruction(0x38), cpu, mem);
	impl::test_pha(*e.instruction(0x48), cpu, mem);
	impl::test_cli(*e.instruction(0x58), cpu, mem);
	impl::test_pla(*e.instruction(0x68), cpu, mem);
	impl::test_sei(*e.instruction(0x78), cpu, mem);
	impl::test_dey(*e.instruction(0x88), cpu, mem);
	impl::test_tya(*e.instruction(0x98), cpu, mem);
	impl::test_tay(*e.instruction(0xa8), cpu, mem);
	impl::test_clv(*e.instruction(0xb8), cpu, mem);
	impl::test_iny(*e.instruction(0xc8), cpu, mem);
	impl::test_cld(*e.instruction(0xd8), cpu, mem);
	impl::test_inx(*e.instruction(0xe8), cpu, mem);
	impl::test_sed(*e.instruction(0xf8), cpu, mem);
}

void do_relative_tests() {
	Executor e;
	CPU cpu;
	Memory mem;

	rel::test_bpl(*e.instruction(0x10), cpu, mem);
	rel::test_bmi(*e.instruction(0x30), cpu, mem);
	rel::test_bvc(*e.instruction(0x50), cpu, mem);
	rel::test_bvs(*e.instruction(0x70), cpu, mem);
	rel::test_bcc(*e.instruction(0x90), cpu, mem);
	rel::test_bcs(*e.instruction(0xb0), cpu, mem);
	rel::test_bne(*e.instruction(0xd0), cpu, mem);
	rel::test_beq(*e.instruction(0xf0), cpu, mem);
}

void do_absolute_tests() {
	Executor e;
	CPU cpu;
	Memory mem;

	abso::test_jsr(*e.instruction(0x20), cpu, mem);
	
	abso::test_bit(*e.instruction(0x2c), cpu, mem);
	abso::test_jmp(*e.instruction(0x4c), cpu, mem);
	abso::test_sty(*e.instruction(0x8c), cpu, mem);
	abso::test_ldy(*e.instruction(0xac), cpu, mem);
	abso::test_cpy(*e.instruction(0xcc), cpu, mem);
	abso::test_cpx(*e.instruction(0xec), cpu, mem);

	abso::test_ora(*e.instruction(0x0d), cpu, mem);
	abso::test_and(*e.instruction(0x2d), cpu, mem);
	abso::test_eor(*e.instruction(0x4d), cpu, mem);
}

namespace abso {

	void test_eor(Instruction& eor, CPU& cpu, Memory& mem) {

	}

	void test_and(Instruction& _and, CPU& cpu, Memory& mem) {
		// AND value point to in memory with the accumulator
		cpu.pc = 0x33;
		cpu.acc = 0xcc; // 11001100
		mem[cpu.pc + 1] = 0x22;
		mem[cpu.pc + 2] = 0x44;
		mem[0x4422] = 0xaa; // 10101010
		_and(cpu, mem);
		// result should be 10001000 (0x88)
		assert(cpu.acc == 0x88);
		assert(cpu.p_n());
		assert(!cpu.p_z());
	}

	void test_cpx(Instruction& cpx, CPU& cpu, Memory& mem) {
		// set flags depending on the comparison of Y and the value pointed to in memory
		// X < M
		cpu.pc = 0x21;
		cpu.x = 0x33;
		mem[cpu.pc + 1] = 0x22; // lo
		mem[cpu.pc + 2] = 0x33; // hi
		mem[0x3322] = 0x55;
		cpx(cpu, mem);
		assert(cpu.pc == 0x24);
		assert(cpu.p_n());
		assert(!cpu.p_z());
		assert(!cpu.p_c());

		// X >= M
		cpu.pc = 0x21;
		cpu.x = 0x66;
		mem[cpu.pc + 1] = 0x22; // lo
		mem[cpu.pc + 2] = 0x33; // hi
		mem[0x3322] = 0x33;
		cpx(cpu, mem);
		assert(cpu.pc == 0x24);
		assert(!cpu.p_n());
		assert(!cpu.p_z());
		assert(cpu.p_c());

		// X == M
		cpu.pc = 0x21;
		cpu.x = 0x55;
		mem[cpu.pc + 1] = 0x22; // lo
		mem[cpu.pc + 2] = 0x33; // hi
		mem[0x3322] = 0x55;
		cpx(cpu, mem);
		assert(cpu.pc == 0x24);
		assert(!cpu.p_n());
		assert(cpu.p_z());
		assert(cpu.p_c());
	}

	void test_cpy(Instruction& cpy, CPU& cpu, Memory& mem) {
		// set flags depending on the comparison of Y and the value pointed to in memory
		// Y < M
		cpu.pc = 0x21;
		cpu.y = 0x33;
		mem[cpu.pc + 1] = 0x22; // lo
		mem[cpu.pc + 2] = 0x33; // hi
		mem[0x3322] = 0x55;
		cpy(cpu, mem);
		assert(cpu.pc == 0x24);
		assert(cpu.p_n());
		assert(!cpu.p_z());
		assert(!cpu.p_c());

		// Y >= M
		cpu.pc = 0x21;
		cpu.y = 0x66;
		mem[cpu.pc + 1] = 0x22; // lo
		mem[cpu.pc + 2] = 0x33; // hi
		mem[0x3322] = 0x33;
		cpy(cpu, mem);
		assert(cpu.pc == 0x24);
		assert(!cpu.p_n());
		assert(!cpu.p_z());
		assert(cpu.p_c());

		// Y == M
		cpu.pc = 0x21;
		cpu.y = 0x55;
		mem[cpu.pc + 1] = 0x22; // lo
		mem[cpu.pc + 2] = 0x33; // hi
		mem[0x3322] = 0x55;
		cpy(cpu, mem);
		assert(cpu.pc == 0x24);
		assert(!cpu.p_n());
		assert(cpu.p_z());
		assert(cpu.p_c());
	}

	void test_ldy(Instruction& ldy, CPU& cpu, Memory& mem) {
		cpu.pc = 0x20;
		cpu.y = 0x34;
		mem[cpu.pc + 1] = 0x10; // lo
		mem[cpu.pc + 2] = 0x20; // hi
		mem[0x2010] = 0x54;
		ldy(cpu, mem);
		assert(cpu.y == mem[0x2010]);
		assert(cpu.pc == 0x23);
	}

	void test_sty(Instruction& sty, CPU& cpu, Memory& mem) {
		cpu.pc = 0x20;
		cpu.y = 0x34;
		mem[cpu.pc + 1] = 0x10; // lo
		mem[cpu.pc + 2] = 0x20; // hi
		sty(cpu, mem);
		assert(mem[0x2010] == cpu.y);
		assert(cpu.pc == 0x23);
	}

	void test_jmp(Instruction& jmp, CPU& cpu, Memory& mem) {
		cpu.pc = 0x55;
		mem[cpu.pc + 1] = 0x10; // lo
		mem[cpu.pc + 2] = 0x20; // hi
		jmp(cpu, mem);
		assert(cpu.pc == 0x2010);
	}

	void test_bit(Instruction& bit, CPU& cpu, Memory& mem) {
		// BIT does an AND with the accumulator and the value pointed to at mem and sets status flags according to the result
		// (but does not change the accumulator or any other register)

		// negative flag set
		cpu.acc = 0xff;
		cpu.pc = 0x20;
		mem[cpu.pc + 1] = 0x10; // lo
		mem[cpu.pc + 2] = 0x20; // hi
		mem[0x2010] = 0x80; // 10000000
		bit(cpu, mem);
		// results with 10000000 (0x80), which sets the negative flag only
		assert(cpu.acc == 0xff); // make sure the accumulator didn't change
		assert(cpu.p_n());
		assert(!cpu.p_v());
		assert(!cpu.p_z());
		
		// overflow flag set
		mem[0x2010] = 0x20; // 00100000 
		mem[cpu.pc + 1] = 0x10; // lo
		mem[cpu.pc + 2] = 0x20; // hi
		bit(cpu, mem);
		assert(!cpu.p_n());
		assert(cpu.p_v());
		assert(!cpu.p_z());
		
		// zero flag set
		mem[0x2010] = 0x00;
		mem[cpu.pc + 1] = 0x10; // lo
		mem[cpu.pc + 2] = 0x20; // hi
		bit(cpu, mem);
		assert(!cpu.p_n());
		assert(!cpu.p_v());
		assert(cpu.p_z());
	}

	void test_jsr(Instruction& jsr, CPU& cpu, Memory& mem) {
		cpu.pc = 0x0a; // this will increment to 0x0d 
		cpu.sp = 0;
		mem[cpu.pc + 1] = 0x10; // lo
		mem[cpu.pc + 2] = 0x30; // hi
		jsr(cpu, mem);
		assert(mem[0x1ff] == 0x0c);
		assert(cpu.pc == 0x3010);
	}

	void test_ora(Instruction& ora, CPU& cpu, Memory& mem) {
		// test that when the accumulator is 10101010 ($AA)
		// and the value pointed to by the operand is 01010101 ($55)
		// that the result is 11111111 ($FF)
		// note: this is negative, so the negative bit will be set
		cpu.pc = 0x00;
		cpu.acc = 0xaa;  // 1010 1010
		mem[cpu.pc + 1] = 0x20; // lo
		mem[cpu.pc + 2] = 0x30; // hi
		mem[0x3020] = 0x55; // 0101 0101
		ora(cpu, mem);
		assert(cpu.acc == 0xff);
		assert(cpu.pc == 0x03);
		assert(!cpu.p_z());
		assert(cpu.p_n());

		// special case with result as 0
		cpu.acc = 0;
		cpu.pc = 0x00;
		mem[0x3020] = 0;
		ora(cpu, mem);
		assert(cpu.acc == 0x00);
		assert(cpu.pc == 0x03);
		assert(cpu.p_z());
		assert(!cpu.p_n());

		// non-negative, non-zero
		cpu.acc = 1;
		cpu.pc = 0x00;
		mem[0x3020] = 2;
		ora(cpu, mem);
		assert(cpu.acc == 3);
		assert(cpu.pc == 0x03);
		assert(!cpu.p_z());
		assert(!cpu.p_n());
	}

}

namespace rel {

	void test_branching(Instruction& i, function<void(CPU&)> positive, function<void(CPU&)> negative) {
		CPU cpu;
		Memory mem;

		positive(cpu);
		cpu.pc = 0;

		// do the jump
		mem[cpu.pc + 1] = 0x45; // this is how far forward the PC should be set on positive evaluation
		i(cpu, mem);
		assert(cpu.pc == 0x47);

		// again?
		mem[cpu.pc + 1] = 0x45;
		i(cpu, mem);
		assert(cpu.pc == 0x8e);

		// what about negative jump?
		mem[cpu.pc + 1] = 0x80;
		i(cpu, mem);
		assert(cpu.pc == 0x10);

		// what about no jump?
		negative(cpu);
		i(cpu, mem);
		assert(cpu.pc == 0x12); // ensure relatives are pushing the right pc increment}
	}

	void test_beq(Instruction& beq, CPU& cpu, Memory& mem) {
		auto positive = [](CPU& cpu) { cpu.p_z(true); };
		auto negative = [](CPU& cpu) { cpu.p_z(false); };
		test_branching(beq, positive, negative);
	}

	void test_bne(Instruction& bne, CPU& cpu, Memory& mem) {
		auto positive = [](CPU& cpu) { cpu.p_z(false); };
		auto negative = [](CPU& cpu) { cpu.p_z(true); };
		test_branching(bne, positive, negative);
	}

	void test_bcs(Instruction& bcs, CPU& cpu, Memory& mem) {
		auto positive = [](CPU& cpu) { cpu.p_c(false); };
		auto negative = [](CPU& cpu) { cpu.p_c(true); };
		test_branching(bcs, positive, negative);
	}

	void test_bcc(Instruction& bcc, CPU& cpu, Memory& mem) {
		auto positive = [](CPU& cpu) { cpu.p_c(true); };
		auto negative = [](CPU& cpu) { cpu.p_c(false); };
		test_branching(bcc, positive, negative);
	}

	void test_bvs(Instruction& bvs, CPU& cpu, Memory& mem) {
		auto positive = [](CPU& cpu) { cpu.p_v(true); };
		auto negative = [](CPU& cpu) { cpu.p_v(false); };
		test_branching(bvs, positive, negative);
	}

	void test_bvc(Instruction& bvc, CPU& cpu, Memory& mem) {
		auto positive = [](CPU& cpu) { cpu.p_v(false); };
		auto negative = [](CPU& cpu) { cpu.p_v(true); };
		test_branching(bvc, positive, negative);
	}

	void test_bmi(Instruction& bmi, CPU& cpu, Memory& mem) {
		auto positive = [](CPU& cpu) { cpu.p_n(true); };
		auto negative = [](CPU& cpu) { cpu.p_n(false); };
		test_branching(bmi, positive, negative);
	}

	void test_bpl(Instruction& bpl, CPU& cpu, Memory& mem) {
		auto positive = [](CPU& cpu) { cpu.p_n(false); };
		auto negative = [](CPU& cpu) { cpu.p_n(true); };
		test_branching(bpl, positive, negative);
	}

}

namespace impl {

	void test_brk(Instruction& brk, CPU& cpu, Memory& mem) {
		// TODO
	}

	void test_rti(Instruction& rti, CPU& cpu, Memory& mem) {
		// TODO
	}

	void test_rts(Instruction& rts, CPU& cpu, Memory& mem) {
		// TODO: i feel like this isn't working right...
		mem[0x1ff] = 0x30; // lo
		mem[0x1fe] = 0x40; // hi (maybe backwards?)
		cpu.sp = 2;
		cpu.pc = 0x0000;
		rts(cpu, mem);
		assert(cpu.pc == 0x4031);
		assert(cpu.sp == 0);
	}

	void test_txa(Instruction& txa, CPU& cpu, Memory& mem) {
		cpu.x = 0x10;
		cpu.acc = 0x20;
		txa(cpu, mem);
		assert(cpu.acc == cpu.x);
		assert(!cpu.p_z());
		assert(!cpu.p_n());

		cpu.x = 0x00;
		cpu.acc = 0x20;
		txa(cpu, mem);
		assert(cpu.acc == cpu.x);
		assert(cpu.p_z());
		assert(!cpu.p_n());

		cpu.x = 0x80;
		cpu.acc = 0x20;
		txa(cpu, mem);
		assert(cpu.acc == cpu.x);
		assert(cpu.p_n());
		assert(!cpu.p_z());
	}

	void test_txs(Instruction& txs, CPU& cpu, Memory& mem) {
		cpu.x = 0x77;
		cpu.sp = 0x88;
		txs(cpu, mem);
		assert(cpu.sp == cpu.x);
	}

	void test_tax(Instruction& tax, CPU& cpu, Memory& mem) {
		cpu.acc = 0x17;
		cpu.x = 0x18;
		tax(cpu, mem);
		assert(cpu.x == cpu.acc);
		assert(!cpu.p_n());
		assert(!cpu.p_z());

		cpu.acc = 0x87;
		cpu.x = 0x18;
		tax(cpu, mem);
		assert(cpu.x == cpu.acc);
		assert(cpu.p_n());
		assert(!cpu.p_z());

		cpu.acc = 0x00;
		cpu.x = 0x18;
		tax(cpu, mem);
		assert(cpu.x == cpu.acc);
		assert(!cpu.p_n());
		assert(cpu.p_z());
	}

	void test_tsx(Instruction& tsx, CPU& cpu, Memory& mem) {
		cpu.sp = 0x22;
		cpu.x = 0x11;
		tsx(cpu, mem);
		assert(cpu.x == cpu.sp);
	}

	void test_dex(Instruction& dex, CPU& cpu, Memory& mem) {
		cpu.x = 0x11;
		dex(cpu, mem);
		assert(cpu.x == 0x10);
		assert(!cpu.p_n());
		assert(!cpu.p_z());

		cpu.x = 0x81;
		dex(cpu, mem);
		assert(cpu.x == 0x80);
		assert(cpu.p_n());
		assert(!cpu.p_z());

		cpu.x = 0x01;
		dex(cpu, mem);
		assert(cpu.x == 0x00);
		assert(!cpu.p_n());
		assert(cpu.p_z());
	}

	void test_nop(Instruction& nop, CPU& cpu, Memory& mem) {
		CPU tempCPU = CPU(cpu);
		nop(cpu, mem);
		assert(cpu.acc == tempCPU.acc);
		assert(cpu.pc == tempCPU.pc + 1);
		assert(cpu.sp == tempCPU.sp);
		assert(cpu.x == tempCPU.x);
		assert(cpu.y == tempCPU.y);
		assert(cpu.p == tempCPU.p);
	}

	void test_sed(Instruction& sed, CPU& cpu, Memory& mem) {
		cpu.p_d(false);
		sed(cpu, mem);
		assert(cpu.p_d());
	}

	void test_inx(Instruction& inx, CPU& cpu, Memory& mem) {
		cpu.x = 0x77;
		inx(cpu, mem);
		assert(cpu.x == 0x78);
		assert(!cpu.p_n());
		assert(!cpu.p_z());

		cpu.x = 0xff;
		inx(cpu, mem);
		assert(cpu.x == 0x00);
		assert(!cpu.p_n());
		assert(cpu.p_z());

		cpu.x = 0x7f;
		inx(cpu, mem);
		assert(cpu.x == 0x80);
		assert(cpu.p_n());
		assert(!cpu.p_z());
	}

	void test_cld(Instruction& cld, CPU& cpu, Memory& mem) {
		cpu.p_d(true);
		cld(cpu, mem);
		assert(!cpu.p_d());
	}

	void test_iny(Instruction& iny, CPU& cpu, Memory& mem) {
		cpu.y = 0x77;
		iny(cpu, mem);
		assert(cpu.y == 0x78);
		assert(!cpu.p_n());
		assert(!cpu.p_z());

		cpu.y = 0xff;
		iny(cpu, mem);
		assert(cpu.y == 0x00);
		assert(!cpu.p_n());
		assert(cpu.p_z());

		cpu.y = 0x7f;
		iny(cpu, mem);
		assert(cpu.y == 0x80);
		assert(cpu.p_n());
		assert(!cpu.p_z());
	}

	void test_clv(Instruction& clv, CPU& cpu, Memory& mem) {
		cpu.p_v(true);
		clv(cpu, mem);
		assert(!cpu.p_v());
	}

	void test_tay(Instruction& tay, CPU& cpu, Memory& mem) {
		cpu.acc = 0x10;
		cpu.y = 0x20;
		tay(cpu, mem);
		assert(cpu.y == cpu.acc);
		assert(!cpu.p_z());
		assert(!cpu.p_n());

		cpu.acc = 0x00;
		cpu.y = 0x20;
		tay(cpu, mem);
		assert(cpu.acc == cpu.y);
		assert(cpu.p_z());
		assert(!cpu.p_n());

		cpu.acc = 0x80;
		cpu.y = 0x20;
		tay(cpu, mem);
		assert(cpu.acc == cpu.y);
		assert(cpu.p_n());
		assert(!cpu.p_z());
	}

	void test_tya(Instruction& tya, CPU& cpu, Memory& mem) {
		cpu.y = 0x10;
		cpu.acc = 0x20;
		tya(cpu, mem);
		assert(cpu.acc == cpu.y);
		assert(!cpu.p_z());
		assert(!cpu.p_n());

		cpu.y = 0x00;
		cpu.acc = 0x20;
		tya(cpu, mem);
		assert(cpu.acc == cpu.y);
		assert(cpu.p_z());
		assert(!cpu.p_n());

		cpu.y = 0x80;
		cpu.acc = 0x20;
		tya(cpu, mem);
		assert(cpu.acc == cpu.y);
		assert(cpu.p_n());
		assert(!cpu.p_z());
	}

	void test_dey(Instruction& dey, CPU& cpu, Memory& mem) {
		cpu.y = 0x10;
		dey(cpu, mem);
		assert(cpu.y == 0x0f);
		assert(!cpu.p_z());
		assert(!cpu.p_n());

		cpu.y = 0x01;
		dey(cpu, mem);
		assert(cpu.y == 0);
		assert(cpu.p_z());
		assert(!cpu.p_n());

		// test when the value is negative (I think it still straight decrements?)
		// 10000001 => 10000000 (0x81 -> DEY -> 0x80)
		cpu.y = 0x81;
		dey(cpu, mem);
		assert(cpu.y == 0x80);
		assert(!cpu.p_z());
		assert(cpu.p_n());
	}

	void test_sei(Instruction& sei, CPU& cpu, Memory& mem) {
		cpu.p_i(false);
		sei(cpu, mem);
		assert(cpu.p_i());
	}

	void test_pla(Instruction& pla, CPU& cpu, Memory& mem) {
		cpu.acc = 0x77;
		cpu.sp = 0x02;
		mem[0x1fe] = 0x66;
		pla(cpu, mem);
		assert(cpu.acc == 0x66);
		assert(cpu.sp == 0x01);
	}

	void test_cli(Instruction& cli, CPU& cpu, Memory& mem) {
		cpu.p_i(true);
		cli(cpu, mem);
		assert(!cpu.p_i());
	}

	void test_pha(Instruction& pha, CPU& cpu, Memory& mem) {
		cpu.acc = 0x66;
		cpu.sp = 0;
		mem[0x1ff] = 0x00;
		pha(cpu, mem);
		assert(mem[0x1ff] == cpu.acc);
	}

	void test_sec(Instruction& sec, CPU& cpu, Memory& mem) {
		cpu.p_c(false);
		sec(cpu, mem);
		assert(cpu.p_c());
	}

	void test_plp(Instruction& plp, CPU& cpu, Memory& mem) {
		cpu.p = 0x70;
		cpu.sp = 0x44;
		mem.push_stack(cpu.sp, 0x10);
		plp(cpu, mem);
		assert(cpu.p == 0x10);
		assert(cpu.sp == 0x44);
	}

	void test_php(Instruction& php, CPU& cpu, Memory& mem) {
		// PHP: push the status register onto the stack
		cpu.sp = 0;
		cpu.p = 0x70;
		assert(mem[0x1ff] != cpu.p);
		php(cpu, mem);
		assert(cpu.sp == 1);
		assert(mem[0x1ff] == cpu.p);
		php(cpu, mem);
		php(cpu, mem);
		assert(cpu.sp == 3);
		assert(mem[0x1fe] == cpu.p);
		assert(mem[0x1fd] == cpu.p);
	}

	void test_clc(Instruction& clc, CPU& cpu, Memory& mem) {
		// CLC: clear the carry flag on the status register
		cpu.p_c(true);
		clc(cpu, mem);
		assert(!cpu.p_c());
		cpu.p_c(false);
		clc(cpu, mem);
		assert(!cpu.p_c());
	}

}

int do_asm_tests() {
	cout << "Running tests" << endl;

	Assembler assembler;

	vector<unsigned char> result;
	string resultstr;

	result = assembler.decodeline(string("BRK"));
	resultstr = make_string(result);
	assert(resultstr == string("00"));

	result = assembler.decodeline(string("BPL $00"));
	resultstr = make_string(result);
	assert(resultstr == string("10FD"));

	result = assembler.decodeline(string("BPL $10"));
	resultstr = make_string(result);
	assert(resultstr == string("100B"));

	return 0;
}

string make_string(vector<unsigned char>& in) {
	ostringstream ss;

	for (auto c : in) {
		if (c < 10) ss << '0';
		ss << hex << (int) c;
	}

	return ss.str();
}


void do_full_program_tests() {

	/* 38 B0 00 20 07 80 18 C8 60 ==>
	$8000: SEC
	$8001: BCS $01
	$8003: INX
	$8004: JSR $08 $80
	$8007: CLC
	$8008: INY
	$8009: RTS # will fail on the second loop since the return address no longer exists on the stack
	*/	

	Executor e;
	e.load("test.s");
	e.run();
}
