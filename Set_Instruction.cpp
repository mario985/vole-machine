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
// void Set_Instruction::SetInput(string input){
//     Input=input;
// }
void Set_Instruction::ChooseMethod(string input , Registers &Reg , Memory &Mem , string*ptr){
    Input = input;
    if(Input[0]=='1' || Input[0]=='2')Load(Reg,Mem);
    else if(Input[0]=='3')Store(Reg,Mem);
    else if(Input[0]=='4')Move(Reg);
    else if(Input[0]=='B'){
        // if(Jump(Reg)){
        //     string Memloc;
        //     Memloc[0]=Input[2],Memloc[1]=Input[3];
        //     ptr = &Mem.Mem_Slots[stoi(Memloc)];
        //     return;
        // }
    }
}
void Set_Instruction::Load(Registers &Regs , Memory &Mem){//1058 == R0 =M58    2058 == R0 = 58
    string RegNumber,MemNumber,Operation;
    Operation = Input[0],RegNumber+=Input[1],MemNumber+=Input[2],MemNumber+=Input[3];
   if(Operation=="1"){
    Regs.SetValues(Mem.Get_Value(stoi(MemNumber)) , stoi(RegNumber));
    return;
   }
   Regs.SetValues(MemNumber,stoi(RegNumber));
}
void Set_Instruction::Store(Registers & Regs , Memory & Mem){//3158  == M58 = R1
    string RegNumber;
    // RegNumber=Input[1];
    // int MemNumber = (Input[2] - '0') * 10 + (Input[3] - '0');
    // Regs.SetValues(Mem.Get_Value((MemNumber)) , stoi(RegNumber));
}
void Set_Instruction::Move(Registers &Regs){//4056 == R6 = R5
    string Reg1,Reg2;
    Reg1=Input[2],  Reg2 = Input[3];
    Regs.SetValues(Regs.GetValues(stoi(Reg1)) , stoi(Reg2));
}
bool Set_Instruction::Jump(Registers &Regs){
   int Reg_Index = Input[1] - '0';
   return Regs.GetValues(Reg_Index)==Regs.GetValues(0);
}



