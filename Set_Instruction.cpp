#include "Set_Instruction.h"
#include "Registers.h"
#include "Memory.h"
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <iomanip>
using namespace std;
void Set_Instruction::ChooseMethod(const string& input, Registers& Reg, Memory& Mem, string*& ptr) {
    Input = input;
    char opCode = Input[0];
    if (opCode == '1' || opCode == '2') {
        Load(Reg, Mem);
    } else if (opCode == '3') {
        Store(Reg, Mem);
    } else if (opCode == '4') {
        Move(Reg);
    } else if (opCode == 'B' && Jump(Reg)) {
        ptr = &Mem.Mem_Slots[HexToDec(Input.substr(2, 2))];
        return;
    }
    ptr++;  // Increment pointer after each operation
}
void Set_Instruction::Load(Registers& Regs, Memory& Mem) {
    char operation = Input[0];
    int regIdx = HexToDec(Input.substr(1, 1));
    int memAddr = HexToDec(Input.substr(2, 2));

    if (operation == '1') {
        Regs.SetValues(Mem.Get_Value(memAddr), regIdx);
    } else {
        Regs.SetValues(Input.substr(2, 2), regIdx); // Load immediate value
    }
}

void Set_Instruction::Store(Registers& Regs, Memory& Mem) {
    int regIdx = HexToDec(Input.substr(1, 1));
    int memAddr = HexToDec(Input.substr(2, 2));
    Mem.Set_Value(Regs.GetValues(regIdx), memAddr);
}

void Set_Instruction::Move(Registers& Regs) {
    int regSrc = HexToDec(Input.substr(2, 1));
    int regDest = HexToDec(Input.substr(3, 1));
    Regs.SetValues(Regs.GetValues(regSrc), regDest);
}

bool Set_Instruction::Jump(Registers& Regs) {
    int regIdx = HexToDec(Input.substr(1, 1));
    return Regs.GetValues(regIdx) == Regs.GetValues(0);
}




