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
class CPU {

protected:
    Memory Mem;
    Registers Reg;
    vector<string>file_content;
    int Program_counter;
    string IR;
    string IR2;
    Set_Instruction Inst;
    ALU AL;

public:
    CPU();
        void RunCode();
        void Step();
        void Import(string filename,int Address);
        bool Is_Valid_Input(const string&name);
        bool File_Check(const string&name);
        Memory& getMem() {
            return Mem;
        }
        string& getIR() {
            return IR;
        }
        string& getIR2() {
            return IR2;
        }
        ALU& getALU() {

            return AL;
        }
        Registers& getReg() {

            return Reg;
        }
        int& getPc() {
            return Program_counter;
        }
        void setPc(int value) {
            Program_counter = value;
        }
        string& getO() {
            return Inst.getOutput();
        }
};
#endif
