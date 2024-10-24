#include "Memory.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
Memory::Memory():Mem_Slots(256){
    for(int i=0;i<256;i++){
        Mem_Slots[i]="00";
    }
}
void Memory::Set_Value(string value , int bit){
    Mem_Slots[bit]=value;
}
string Memory::Get_Value(int bit){
    return Mem_Slots[bit];

}
