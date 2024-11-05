#include "Memory.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
Memory::Memory():Mem_Slots(256){
    Reset();
    
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
