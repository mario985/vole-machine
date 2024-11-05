#ifndef MACHINE_H
#define MACHINE_H
#include "InstInput.h"
#include "Memory.h"
#include "CPU.h"


class Machine{
	CPU processor;
	string output = processor.getO();


public:
	CPU& getCpu() {
		return processor;
	}
	void Import(string filename);
	void setOutput();
};
#endif // !MACHINE_H

