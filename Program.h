#ifndef Program_H
#define Program_H
#include "Registers.h"
#include "Memory.h"
#include "Set_Instruction.h"
#include "ALU.h"
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <iomanip>
using namespace std;
#endif
class Program :public Memory, public ALU {
private:
    Registers Reg;
    Memory Mem;
    Set_Instruction Inst;
    string* ptr;
public:
    Program();
    void modify();
    void print();

};