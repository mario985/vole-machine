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
using namespace std;
using namespace std;
#define slot Mem.Mem_Slots
bool CPU::ChooseMethod(const char & Choice){
    if(Choice=='1')Import("test.txt");
    else if(Choice=='2')print();
    else if(Choice=='3')RunCode();
    else if(Choice=='4')Step();
    else if(Choice=='5')Clear();
    else if(Choice=='6')ClearMemory();
    else if(Choice =='7')ClearRegister();
    else if(Choice == '8'){
        return false;
    }
    return true;

}
CPU::CPU(){
    Program_counter = &slot[0];
}
void CPU::Import(string filename){
    ifstream file ;
    string word;
    file.open(filename , ios::in);
    int BitCounter=0;
    bool End=false;
    while (file >> word ){
     if(File_Check(word)){
        Mem.Set_Value(word.substr(0,2),BitCounter++);
        Mem.Set_Value(word.substr(2,2),BitCounter++);
     }
      if(word=="C000"){
            End=true;
            break;
        }
     }
     if(!End){
        Mem.Set_Value("C0",BitCounter++);
        Mem.Set_Value("00",BitCounter++);

     }
}
void CPU::Step(){
    if(Input=="C000"){
        return;
    }
    Input+=*Program_counter;
    if(Program_counter!=nullptr){
        Program_counter++;
        Input+= (*Program_counter);
    }
    if(Is_Valid_Input(Input)){
    Inst.ChooseInstruction(Input, Reg, Mem, Program_counter);
    }
    else Program_counter++,Input.clear();
    }

void CPU::RunCode(){
    Input.clear();
    Program_counter =&slot[0];
    while(true){
        if(Input=="C000"){
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
    return name.size()==4;
}
void CPU::ClearMemory(){
    Mem.Reset();
}
void CPU::ClearRegister(){
    Reg.Reset();
}
void CPU::Clear(){
    Mem.Reset();
    Reg.Reset();
    Program_counter=&slot[0];
    Input.clear();
}
void CPU::print(){
    cout<<*Program_counter<<endl;
    for (int i = 0; i < 16; i++) {
        cout << "RegIndex[" << DecToHex(to_string(i)) << "]: " << Reg.GetValues(i) << endl;
    }
    cout << "==============" << endl;

    for (int i = 0; i < 256; i++) {
        cout << "MemSlot[" << DecToHex(to_string(i)) << "]: " << Mem.Get_Value(i) << endl;
    }
}