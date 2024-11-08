#ifndef Set_instruction_H
#define Set_instruction_H
#include <iostream>
#include <vector>
#include <string>
#include "Memory.h"
#include "Registers.h"
#include "ALU.h"
#include <bitset>
class Set_Instruction :ALU{
private:
    string Input;
    string outputstr;

public:
     void ChooseInstruction(string & input, Registers &Reg , Memory &Mem ,  int &ptr);
     void Load(Registers &Regs , Memory &Mem);//1058 == R0 =M58    2058 == R0 = 58
     void Store(Registers &Regs , Memory &Mem);//3158  == M58 = R1
     void Move(Registers &Regs);//4056 == R6 = R5
     bool Jump(Registers &Regs);// B543  If(R5 == R0) jump to M43
     void twosCompAdd(Registers &R);
     void BitOR (Registers &Regs );
     void BitAND (Registers &Regs );
     void BitXOR (Registers &Regs );
     bool Jump2(Registers& Regs);
     void FloatAdd(Registers& Regs);
     bool Compare(Registers& R);
     void rotateRight(Registers& Regs);
     void output(Registers &R);
     string& getOutput() {
         return outputstr;
     }

};
#endif
