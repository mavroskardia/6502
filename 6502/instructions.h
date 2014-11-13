#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include "includes.h"

class Instruction {
public:
	Instruction() {}
	virtual ~Instruction() {}
	virtual std::string str() { return "UNKNOWN"; }
	virtual void operator() (CPU&, Memory& memory);
	virtual void execute(CPU&, Memory& memory) = 0;
	virtual void increment_pc(CPU&) = 0;
};

namespace Impl {
	
	class BRK : public Instruction {
		virtual std::string str() { return "BRK"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class RTI : public Instruction {
		virtual std::string str() { return "RTI"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class RTS : public Instruction {
		virtual std::string str() { return "RTS"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class PHP : public Instruction {
		virtual std::string str() { return "PHP"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class PLP : public Instruction {
		virtual std::string str() { return "PLP"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class CLC : public Instruction {
		virtual std::string str() { return "CLC"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class SEC : public Instruction {
		virtual std::string str() { return "SEC"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class PHA : public Instruction {
		virtual std::string str() { return "PHA"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class CLI : public Instruction {
		virtual std::string str() { return "CLI"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class PLA : public Instruction {
		virtual std::string str() { return "PLA"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class SEI : public Instruction {
		virtual std::string str() { return "SEI"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class DEY : public Instruction {
		virtual std::string str() { return "DEY"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class TYA : public Instruction {
		virtual std::string str() { return "TYA"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class TAY : public Instruction {
		virtual std::string str() { return "TAY"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class CLV : public Instruction {
		virtual std::string str() { return "CLV"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class INY : public Instruction {
		virtual std::string str() { return "INY"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class CLD : public Instruction {
		virtual std::string str() { return "CLD"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class INX : public Instruction {
		virtual std::string str() { return "INX"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class SED : public Instruction {
		virtual std::string str() { return "SED"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class TXA : public Instruction {
		virtual std::string str() { return "TXA"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class TXS : public Instruction {
		virtual std::string str() { return "TXS"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class TAX : public Instruction {
		virtual std::string str() { return "TAX"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class TSX : public Instruction {
		virtual std::string str() { return "TSX"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class DEX : public Instruction {
		virtual std::string str() { return "DEX"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

	class NOP : public Instruction {
		virtual std::string str() { return "NOP"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 1; }
	};

}

namespace Rel {
	class BPL : public Instruction {
		virtual std::string str() { return "BPL"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 2; }
	};

	class BMI : public Instruction {
		virtual std::string str() { return "BMI"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 2; }
	};

	class BVC : public Instruction {
		virtual std::string str() { return "BVC"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 2; }
	};

	class BVS : public Instruction {
		virtual std::string str() { return "BVS"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 2; }
	};

	class BCC : public Instruction {
		virtual std::string str() { return "BCC"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 2; }
	};

	class BCS : public Instruction {
		virtual std::string str() { return "BCS"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 2; }
	};

	class BNE : public Instruction {
		virtual std::string str() { return "BNE"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 2; }
	};

	class BEQ : public Instruction {
		virtual std::string str() { return "BEQ"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 2; }
	};

}

namespace Absolute {
	
	class JSR : public Instruction {
		virtual std::string str() { return "JSR"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 3; }
	};

	class BIT : public Instruction {
		virtual std::string str() { return "BIT"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 3; }
	};

	class JMP : public Instruction {
		virtual std::string str() { return "JMP"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 3; }
	};

	class STY : public Instruction {
		virtual std::string str() { return "STY"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 3; }
	};

	class LDY : public Instruction {
		virtual std::string str() { return "LDY"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 3; }
	};

	class CPY : public Instruction {
		virtual std::string str() { return "CPY"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 3; }
	};

	class CPX : public Instruction {
		virtual std::string str() { return "CPX"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 3; }
	};

	class ORA : public Instruction {
		virtual std::string str() { return "ORA"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 3; }
	};

	class AND : public Instruction {
		virtual std::string str() { return "AND"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 3; }
	};

	class EOR: public Instruction {
		virtual std::string str() { return "EOR"; }
		virtual void execute(CPU&, Memory& mem);
		virtual void increment_pc(CPU& cpu) { cpu.pc += 3; }
	};

}

#endif