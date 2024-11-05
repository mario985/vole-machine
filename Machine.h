<<<<<<< HEAD
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

=======
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

>>>>>>> ccb3b64d80a319ab1d95b8035a67d9771c43620a
