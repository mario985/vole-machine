#include"Registers.h"
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
using namespace std;
Registers::Registers():Regs(16){
    Reset();
    
}
void Registers::SetValues(string value,int bit){
    Regs[bit]=value;
}
string Registers::GetValues(int bit){
    return Regs[bit];
}
void Registers::Reset(){
    fill(Regs.begin() , Regs.end() , "00");
}
