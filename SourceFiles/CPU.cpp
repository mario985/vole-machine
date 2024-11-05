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
static int BitCounter = 0 ;
CPU::CPU() { 
    Program_counter = 0;
}

void CPU::Import(string filename,int Address = 0) {

    if(Address<BitCounter-1){
       Program_counter = Address ; 
    }
    Inst.getOutput().clear();
    ifstream file;
    string word;
    file.open(filename, ios::in);
    BitCounter = Address;
    bool End = false;
    while (file >> word) {
        for (char &c : word) {
           if (isalpha(c)) {
               c = toupper(c);
           }
        }
        if (File_Check(word)) {
            Mem.Set_Value(word.substr(0, 2), BitCounter++);
            Mem.Set_Value(word.substr(2, 2), BitCounter++);
        }
        if (word == "C000" || BitCounter >= 255) {
            return;
        }
    }
    auto it = find(slot.begin(), slot.end(),"C0");
    if (it == slot.end()) {
        Mem.Set_Value("C0", BitCounter++);
        Mem.Set_Value("00", BitCounter++);
    }
}

void CPU::Step(){
    
    if(IR=="C000" || Program_counter + 1 > 255){
        IR.clear();
        return;
    }
    IR += slot[Program_counter];
    IR += slot[Program_counter+1];
    IR2 = IR;
    if(Is_Valid_Input(IR)){
        Inst.ChooseInstruction(IR, Reg, Mem, Program_counter);
        Program_counter += 2;
        //IR.clear();
    }
    else Program_counter += 2,IR.clear();
}

void CPU::RunCode(){
    IR.clear();
    while(true){
        if(IR=="C000" || Program_counter + 1 > 255){
            Program_counter = 0 ;
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


