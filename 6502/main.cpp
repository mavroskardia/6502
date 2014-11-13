#include "includes.h"

int do_assembly(const char*);
int do_run(const char*);
int do_tests();

int main(int argc, char** argv) {
	int ret = 0;

	switch (argc) {
	case 2:
		ret = string("test").compare(argv[1]) == 0 ? do_tests() : 1;
		break;
	case 3:
		if (string("assemble").compare(argv[1]) == 0) ret = do_assembly(argv[2]);
		else if (string("run").compare(argv[1]) == 0) ret = do_run(argv[2]);
		break;	
	default:
		cout << "usage: " << argv[0] << " <6502 assembly file>" << endl;
		ret = 1;
	}

	return ret;
}

int do_assembly(const char* filename) {
	int ret = 0;
	auto assembler = Assembler(filename);

	cout << "build assembler for file " << filename << endl;

	try {
		while (!assembler.eof()) {
			stringstream lineout;
			lineout << assembler.current_line_number() << ":\t";

			vector<unsigned char> decoded = assembler.decodeline();
			for (auto c : decoded)
				lineout << "0x" << hex << (int)c;

			cout << lineout.str() << endl;
		}
	}
	catch (SyntaxException se) {
		cerr << "Failed to assemble file: " << se.what();
		ret = 1;
	}
	catch (UnknownInstruction ui) {
		cerr << "Failed to assemble file: " << ui.what();
		ret = 1;
	}
	catch (regex_error& re) {
		cerr << "A regular expression failed: " << re.what() << " " << re.code() << endl;
		ret = 1;
	}
	
	return ret;
}

int do_run(const char* filename) {
	int ret = 0;

	Executor e;

	if (e.load(filename)) e.run();

	return ret;
}