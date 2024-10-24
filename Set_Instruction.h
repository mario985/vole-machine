#ifndef Set_instruction_H
#define Set_instruction_H
#include <iostream>
#include <vector>
#include <string>
#include "Memory.h"
#include "Registers.h"
class Set_Instruction{
    private:
    string Input;
    public:
    void ChooseMethod(string input, Registers &Reg , Memory &Mem ,  string*ptr);
    void Load(Registers &Regs , Memory &Mem);//1058 == R0 =M58    2058 == R0 = 58
    void Store(Registers &Regs , Memory &Mem);//3158  == M58 = R1
    void Move(Registers &Regs);//4056 == R6 = R5
    // int hex_to_twos_complement(const string& hexStr, int bitSize);
    // string int_to_twos_complement_hex(int value, int bitSize);
    // string add_hex_twos_complement(const string& hex1, const string& hex2);
    // void Add_TwosComplement(Registers & Regs);//5657 == R6 = R5+R7
    // void Add(Registers &Regs);//6587 == R5 = float(R8)+ float(R7)
    bool Jump(Registers &Regs);// B543  If(R5 == R0) jump to M43
};
#endif