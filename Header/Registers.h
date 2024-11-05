#ifndef Registers_h
#define Registers_h
#include <vector>
#include <iostream>
using namespace std;
const int N = 17;
class Registers{

    vector<string>Regs;
public:

    Registers();
    void SetValues(string value,int bit);
    string GetValues(int bit);
    void Reset();

};
#endif