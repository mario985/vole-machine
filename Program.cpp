#include "Program.h"
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
#define ll long long 
#define slot Mem.Mem_Slots
Program::Program(){
    int count=0;
    string input;
    while(true){
        cin >> input;
        Mem.Set_Value(input.substr(0,2), count++);
        Mem.Set_Value(input.substr(2,4), count++);
        if(input=="C000"){
            break;
        }
        }
        ptr = &slot[0];
}
void Program::modify(){
   while(true)
   {
    string input;
    input += *ptr;
    ptr++;
    input+= *ptr;
    ptr++;
    if(input=="C000"){
        return;
    }
    // Inst.ChooseMethod(input,Reg , Mem , ptr );

   }

}
void Program::print(){
    for(int i=0;i<17;i++){
        cout<<"REgIndex["<<i<<"]: "<<Reg.GetValues(i)<<endl;

    }
    cout<<"=============="<<endl;
    for(int i=0;i<256;i++){
        cout<<"MemSlot["<<i<<"]: "<<Mem.Get_Value(i)<<endl;

    }
    // cout<<endl;

}