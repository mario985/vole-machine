#ifndef Memory_h
#define Memory_h
#include <iostream>
#include<string>
#include <vector>
using namespace std;
class Memory{
public:
    vector<string>Mem_Slots;
    Memory();
    void Set_Value(string value , int bit);
    string Get_Value( int bit);
    void Reset();
};
#endif