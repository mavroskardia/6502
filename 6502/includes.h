#ifndef __INCLUDES_H_
#define __INCLUDES_H_

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <thread>
#include <map>
#include <vector>

#ifdef _DEBUG
#define dbgout(x) cout << x
#else
#define dbgout(x) 
#endif

#include "exceptions.h"
#include "cpu.h"
#include "memory.h"
#include "instructions.h"
#include "tokenizer.h"
#include "disassembler.h"
#include "assembler.h"
#include "executor.h"


#endif // __INCLUDES_H_
