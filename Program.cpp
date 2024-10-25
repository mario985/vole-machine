// #include "Program.h"
// #include "Set_Instruction.h"
// #include "Registers.h"
// #include "Memory.h"
// #include "ALU.h"
// #include <iostream>
// #include <vector>
// #include <string>
// #include <bitset>
// #include <sstream>
// #include <iomanip>
// using namespace std;
// #define ll long long 
// #define slot Mem.Mem_Slots
// Program::Program(){
//     int count=0;
//     string input;
//     while(true){
//     cin>>input;
//     Mem.Set_Value(input.substr(0,2), count++);
//     Mem.Set_Value(input.substr(2,2), count++);
//     if(input=="C000"){
//         break;
//     }
//     }
//     ptr = &slot[0];
// }
// void Program::modify(){
//    while(true)
//    {
//     string input;
//     input += *ptr;
//     ptr++;
//     input+= *ptr;
//     if(input=="C000" ||input=="0000"){
//         return;
//     }
//     if(Is_Valid(input))Inst.ChooseMethod(input,Reg , Mem , ptr );
//     else ptr++;
//    }

// }
// void Program::print(){
//     string Index;
//     for(int i=0;i<16;i++){
//         Index=i;
//         cout<<"REgIndex["<<DecToHex(to_string(i))<<"]: "<<Reg.GetValues(i)<<endl;

//     }
//     cout<<"=============="<<endl;
//     for(int i=0;i<256;i++){
//         Index=i;
//         cout<<"MemSlot["<<DecToHex(to_string(i))<<"]: "<<Mem.Get_Value(i)<<endl;

//     }
//     // cout<<endl;

// }
#include "Program.h"
#include "Set_Instruction.h"
#include "Registers.h"
#include "Memory.h"
#include "ALU.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

#define slot Mem.Mem_Slots

Program::Program() {
    int count = 0;
    string input;
    while (true) {
        cin >> input;
        Mem.Set_Value(input.substr(0, 2), count++);
        Mem.Set_Value(input.substr(2, 2), count++);
        if (input == "C000") break;
    }
    ptr = &slot[0];
}

void Program::modify() {
    while (true) {
        string input;
        input += *ptr++;
        input += *ptr;

        if (input == "C000" || input == "0000") return;

        if (Is_Valid(input)) {
            Inst.ChooseMethod(input, Reg, Mem, ptr);
        } else {
            ptr++;
        }
    }
}

void Program::print() {
    for (int i = 0; i < 16; i++) {
        cout << "RegIndex[" << DecToHex(to_string(i)) << "]: " << Reg.GetValues(i) << endl;
    }
    cout << "==============" << endl;

    for (int i = 0; i < 256; i++) {
        cout << "MemSlot[" << DecToHex(to_string(i)) << "]: " << Mem.Get_Value(i) << endl;
    }
}
