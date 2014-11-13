#include "includes.h"

bool CPU::p_n() { return (p & 0x80) > 0; } // negative		10000000
bool CPU::p_v() { return (p & 0x40) > 0; } // overflow		01000000
bool CPU::p_b() { return (p & 0x10) > 0; } // break			00010000
bool CPU::p_d() { return (p & 0x08) > 0; } // decimal		00001000
bool CPU::p_i() { return (p & 0x04) > 0; } // interrupt		00000100
bool CPU::p_z() { return (p & 0x02) > 0; } // zero			00000010
bool CPU::p_c() { return (p & 0x01) > 0; } // carry			00000001

void CPU::p_n(bool t) { if (t) p |= 0x80; else p &= 0x7f; }
void CPU::p_v(bool t) { if (t) p |= 0x40; else p &= 0xbf; }
void CPU::p_b(bool t) { if (t) p |= 0x10; else p &= 0x77; }
void CPU::p_d(bool t) { if (t) p |= 0x08; else p &= 0xf7; }
void CPU::p_i(bool t) { if (t) p |= 0x04; else p &= 0xfb; }
void CPU::p_z(bool t) { if (t) p |= 0x02; else p &= 0xfd; }
void CPU::p_c(bool t) { if (t) p |= 0x01; else p &= 0xfe; }

std::string CPU::str() {
	std::ostringstream ss;
	ss << "PC: $" << hex << pc << " SP: $" << hex << (int)sp;
	ss << " ACC: $" << hex << (int)acc << " X: $" << hex << (int)x << " Y: $" << hex << (int)y;
	ss << " NV-BDIZC: ";
	ss << (int)p_n() << (int)p_v() << "-" << (int)p_b();
	ss << (int)p_d() << (int)p_i() << (int)p_z();
	ss << (int)p_c();
	return ss.str();
}