#ifndef MACHINE_H
#define MACHINE_H
#include "Memory.h"
#include "CPU.h"

class Machine{
	CPU processor;
	/*Memory Mem = processor.getMem();*/


public:
	CPU& getCpu() {
		return processor;
	}
	/*Memory& getMem() {
		return Mem;
	}*/
	void Import(string filename);
	void output();
};
#endif // !MACHINE_H

