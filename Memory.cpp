#include "Memory.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
Memory::Memory():Mem_Slots(256){
    Reset();
    Mem_Slots[0] = "20";
    Mem_Slots[1] = "11";
    Mem_Slots[2] = "21";
    Mem_Slots[3] = "20";
    Mem_Slots[4] = "C0";
    Mem_Slots[5] = "00";
}
void Memory::Set_Value(string value , int bit){
    Mem_Slots[bit]=value;
}
string Memory::Get_Value(int bit){
    return Mem_Slots[bit];

}
void Memory::Reset(){
    fill(Mem_Slots.begin() , Mem_Slots.end() , "00");
}
