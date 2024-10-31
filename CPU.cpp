#include "Memory.h"
#include "Registers.h"
#include "ALU.h"
#include "CPU.h"
#include "Set_Instruction.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <regex>
#include <fstream>
#define slot Mem.Mem_Slots
using namespace std;

CPU::CPU() {
    Program_counter = 0;
}
//bool CPU::ChooseMethod(const char & Choice){
//    if(Choice=='1')Import("test.txt");
//    else if(Choice=='2')print();
//    else if(Choice=='3')RunCode();
//    else if(Choice=='4')Step();
//    else if(Choice=='5')Clear();
//    else if(Choice=='6')ClearMemory();
//    else if(Choice =='7')ClearRegister();
//    else if(Choice == '8'){
//        return false;
//    }
//    return true;
//
//}
void CPU::Import(string filename) {
    ifstream file;
    string word;
    file.open(filename, ios::in);
    int BitCounter = 0;
    bool End = false;
    while (file >> word) {
        if (File_Check(word)) {
            Mem.Set_Value(word.substr(0, 2), BitCounter++);
            Mem.Set_Value(word.substr(2, 2), BitCounter++);
        }
        if (word == "C000") {
            End = true;
            break;
        }
    }
    if (!End) {
        Mem.Set_Value("C0", BitCounter++);
        Mem.Set_Value("00", BitCounter++);

    }
}

void CPU::Step(){
    if(IR=="C000"){
        return;
    }
    IR += slot[Program_counter];
    IR+= slot[Program_counter+1];
      
    if(Is_Valid_Input(IR)){
        Inst.ChooseInstruction(IR, Reg, Mem, Program_counter);
        Program_counter += 2;
    }
    else Program_counter += 2,IR.clear();
}

void CPU::RunCode(){
    IR.clear();
    Program_counter = 0;
    while(true){
        if(IR=="C000"){
            return;
        }
        Step();
    }
}

bool CPU::Is_Valid_Input(const string&input){
    bool check = 0 ;
    //regex pattern (R"([-+]?[0-9]+[/]?[-+]?[0-9]*[1-9]*\s[-+*/]\s[-+]?[0-9][0-9]*[/]?[-+]?[0-9]*[1-9]*)") ;
    regex pattern(R"([1-9ABCD][0-9A-F]{1}[0-9A-F]{1}[0-9A-F]{1})");
    if(!(regex_match (input , pattern))){
        return false;
    }
    if (input[0] == 'C' && input.substr(1,3) != "000")
    {
        return false ;
    }
    if (input[0] == '4' && input[1] != '0')
    {
        return false;
    }
    return true ;
    
}
bool CPU::File_Check(const string&name){
    return name.size() == 4;
}

void CPU::ClearRegister(){
    Reg.Reset();
}
//void CPU::Clear(){
//    Mem.Reset();
//    Reg.Reset();
//    Program_counter=&slot[0];
//    IR.clear();
//}
