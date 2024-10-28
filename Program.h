#ifndef Program_H
#define Program_H
#include "Registers.h"
#include "Memory.h"
#include "Set_Instruction.h"
#include "ALU.h"
#include "CPU.h"
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <iomanip>
using namespace std;
#endif
class Program :public CPU {
private:
CPU cpu;
vector<char>Choices;
public:
    Program();
    void MainMenu();

};