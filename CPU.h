#ifndef CPU_h
#define CPU_h
#include "Memory.h"
#include "Registers.h"
#include "ALU.h"
#include "Set_Instruction.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <regex>
#include <fstream>
using namespace std;
class CPU:public ALU{
    private:
    Memory Mem;
    Registers Reg;
    vector<string>file_content;
    string *Program_counter;
    string Input;
    Set_Instruction Inst;
    public:
    CPU();
    bool ChooseMethod(const char & Choice);
    void Import(string filename);
    void RunCode();
    void Step();
    void ClearMemory();
    void ClearRegister();
    void Clear();
    void print();
    bool Is_Valid_Input(const string&name);
    bool File_Check(const string&name);


};
#endif