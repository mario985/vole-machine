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
int main(void){
    Program P;
    P.modify();
    P.print();
}