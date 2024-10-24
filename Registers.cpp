#include"Registers.h"
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
using namespace std;
Registers::Registers():Regs(17){
    for(int i=0 ; i <17;i++)Regs[i]="00";
}
void Registers::SetValues(string value,int bit){
    Regs[bit]=value;
}
string Registers::GetValues(int bit){
    return Regs[bit];
}
