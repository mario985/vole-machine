#include <iostream>
#include <regex>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std ;
// // bool is_valid_input (string input){
// //     bool check = 0 ;
// //     //regex pattern (R"([-+]?[0-9]+[/]?[-+]?[0-9]*[1-9]*\s[-+*/]\s[-+]?[0-9][0-9]*[/]?[-+]?[0-9]*[1-9]*)") ;
// //     regex pattern(R"([1-6BC][0-9A-F]{1}[0-9A-F]{1}[0-9A-F]{1})");
// //     if(!(regex_match (input , pattern))){
// //         return false;
// //     }
// //     if (input[0] == 'C' && input.substr(1,3) != "000")
// //     {
// //         return false ;
// //     }
// //     if (input[0] == '4' && input[1] != '0')
// //     {
// //         return false;
// //     }
// //     return true ;
    
// // }
// // vector <string> file_content ;
// // void read_file (string filename){
// //     ifstream file ;
// //     string word;
// //     file.open(filename , ios::in);
// //     while (file >> word ){
// //         file_content.push_back(word);
        
// //     }

// // }
// // bool file_check (){
// //     bool checker = 0 ;
// //     for (int i = 0 ; i < file_content.size() ; i++){
// //         if (file_content[i].length() != 4){
// //             continue;
// //         }
// //         if (is_valid_input(file_content[i])){
// //             checker = 1 ;
// //         }
// //         else{
// //             checker = 0 ;
// //             break ;
// //         }
    
// // }
// // return checker ;
// // }
// // int main (){
// //     read_file("test.txt");
// //     if (file_check()){
// //         cout << "success" ;
// //     }
// //     else {
// //         cout << "fuck" ;
// //     }
// // }
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
// #include <cmath>
// using namespace std;
// void Set_Instruction::ChooseInstruction(string& input, Registers& Reg, Memory& Mem, string *&ptr) {
//     Input = input;
//     char opCode = Input[0];
//     if (opCode == '1' || opCode == '2') {
//         Load(Reg, Mem);
//     }
//     else if (opCode == '3') {
//         Store(Reg, Mem);
     
//     }
//     else if (opCode == '4') {
//         Move(Reg);
//     }
//     else if (opCode == '5') {
//         twosCompAdd(Reg);
//     }
//     else if (opCode == '6') {
//         FloatAdd(Reg);
//     }
//     else if (opCode == '7') {
//         BitOR(Reg);
//     }
//     else if (opCode == '8') {
//         BitAND(Reg);
//     }
//     else if (opCode == '9') {
//         BitXOR(Reg);
//     }
//     else if (opCode == 'B' && Jump(Reg)) {
//         ptr = &Mem.Mem_Slots[HexToDec(Input.substr(2, 2))];
//         return ;
//     }
//     else if(opCode=='C'){
//         return;
//     }
//     else if (opCode == 'D' && Jump2(Reg)) {
//         ptr = &Mem.Mem_Slots[HexToDec(Input.substr(2, 2))];
//         return;
//     }
//     ptr++;
//     input.clear();
// }
// void Set_Instruction::Load(Registers& Regs, Memory& Mem) {
//     char operation = Input[0];
//     int regIdx = HexToDec(Input.substr(1, 1));
//     int memAddr = HexToDec(Input.substr(2, 2));

//     if (operation == '1') {
//         Regs.SetValues(Mem.Get_Value(memAddr), regIdx);
//     }
//     else {
//         cout<<"Load "<<regIdx<<"With "<<memAddr<<" Bits"<<endl;
//         Regs.SetValues(Input.substr(2, 2), regIdx); // Load immediate value
//     }
// }

// void Set_Instruction::Store(Registers& Regs, Memory& Mem) {
//     int regIdx = HexToDec(Input.substr(1, 1));
//     int memAddr = HexToDec(Input.substr(2, 2));
//     Mem.Set_Value(Regs.GetValues(regIdx), memAddr);
// }

// void Set_Instruction::Move(Registers& Regs) {
//     int regSrc = HexToDec(Input.substr(2, 1));
//     int regDest = HexToDec(Input.substr(3, 1));
//     Regs.SetValues(Regs.GetValues(regSrc), regDest);
// }

// bool Set_Instruction::Jump(Registers& Regs) {
//     int regIdx = HexToDec(Input.substr(1, 1));
//     return Regs.GetValues(regIdx) == Regs.GetValues(0);
// }
// bool Set_Instruction::Jump2(Registers& Regs) {
//     int regIdx = HexToDec(Input.substr(1, 1));
//     return Regs.GetValues(regIdx) > Regs.GetValues(0);
// }
// void Set_Instruction::twosCompAdd(Registers &R) {
//     int regIdxR = HexToDec(Input.substr(1, 1)); // index of reg to store bits at
//     int regIdxS = HexToDec(Input.substr(2, 1)); // index of reg1 to add
//     int regIdxT = HexToDec(Input.substr(3, 1)); // index of reg2 to add
//     string value1 = "0x";
//     string value2 = "0x";
//     value1 += R.GetValues(regIdxS); // Hexa form of the value in the register
//     value2 += R.GetValues(regIdxT);
//     int num1 = stoi(value1, nullptr, 16) - 256; // adjust the 2 numbers in 2's Comp by subtracting 256
//     int num2 = stoi(value2, nullptr, 16) - 256;
//     int res = num1 + num2;
//     string result = DecToHex(to_string(res));
//     result = result.substr(6,2);
//     R.SetValues(result, regIdxR);
// }
// void Set_Instruction::BitOR(Registers& Regs) {
//     int regIdxR = HexToDec(Input.substr(1, 1)); // index of reg to store bits at
//     int regIdxS = HexToDec(Input.substr(2, 1)); // index of reg1 to add
//     int regIdxT = HexToDec(Input.substr(3, 1)); // index of reg2 to add
//     string value1 = "0x";
//     string value2 = "0x";
//     /*
//     2001
//     2121
//     7201
//     */
//     value1 += Regs.GetValues(regIdxS); // Hexa form of the value in the register
//     value2 += Regs.GetValues(regIdxT);
//     int num1 = stoi(value1, nullptr, 16);
//     int num2 = stoi(value2, nullptr, 16);
//     int result = (num1 | num2);
//     string res = DecToHex(to_string(result));
//     if (res.length() == 1) {
//         res.insert(0, "0");
//     }
//     Regs.SetValues(res, regIdxR);

// }
// void Set_Instruction::BitAND(Registers& Regs) {
//     int regIdxR = HexToDec(Input.substr(1, 1)); // index of reg to store bits at
//     int regIdxS = HexToDec(Input.substr(2, 1)); // index of reg1 to add
//     int regIdxT = HexToDec(Input.substr(3, 1)); // index of reg2 to add
//     string value1 = "0x";
//     string value2 = "0x";
//     value1 += Regs.GetValues(regIdxS); // Hexa form of the value in the register
//     value2 += Regs.GetValues(regIdxT);
//     int num1 = stoi(value1, nullptr, 16);
//     int num2 = stoi(value2, nullptr, 16);
//     int result = (num1 & num2);
//     string res = DecToHex(to_string(result));
//     if (res.length() == 1) {
//         res.insert(0, "0");
//     }
//     Regs.SetValues(res, regIdxR);
// }
// void Set_Instruction::BitXOR(Registers& Regs) {
//     int regIdxR = HexToDec(Input.substr(1, 1)); // index of reg to store bits at
//     int regIdxS = HexToDec(Input.substr(2, 1)); // index of reg1 to add
//     int regIdxT = HexToDec(Input.substr(3, 1)); // index of reg2 to add
//     string value1 = "0x";
//     string value2 = "0x";
//     value1 += Regs.GetValues(regIdxS); // Hexa form of the value in the register
//     value2 += Regs.GetValues(regIdxT);
//     int num1 = stoi(value1, nullptr, 16);
//     int num2 = stoi(value2, nullptr, 16);
//     int result = (num1 ^ num2);
//     string res = DecToHex(to_string(result));
//     if (res.length() == 1) {
//         res.insert(0, "0");
//     }
//     Regs.SetValues(res, regIdxR);
// }
// void Set_Instruction::FloatAdd(Registers &Regs) {
//     int regIdxR = HexToDec(Input.substr(1, 1)); // index of reg to store bits at
//     string H1 = Input.substr(2, 1); // index of reg1 to add
//     string H2 = Input.substr(3, 1); // index of reg2 to add
//     string bnr1 = bitset<8>(stoul(H1, nullptr, 16)).to_string();
//     string bnr2 = bitset<8>(stoul(H2, nullptr, 16)).to_string();
//     int sgn1 = stoi(bnr1.substr(0, 1));
//     int sgn2 = stoi(bnr2.substr(0, 1));
//     int exp1 = bitset<8>(bnr1.substr(1, 3)).to_ulong();
//     int exp2 = bitset<8>(bnr2.substr(1, 3)).to_ulong();
//     string mantesa1 = "0." + bnr1.substr(4, 8);
//     double man1 = binaryFractionToDecimal(mantesa1);
//     string mantesa2 = "0." + bnr2.substr(4, 8);
//     double man2 = binaryFractionToDecimal(mantesa2);
//     double res1 = pow(-1, sgn1) * pow(2, exp1 - 4) * double(1 + man1);
//     double res2 = pow(-1, sgn2) * pow(2, exp2 - 4) * double(1 + man2);
//     double res3 = res1 + res2;
//     string sgn3 = "0";
//     if ((res3 < 0)) {
//         sgn3 = '1';
//         res3 = -1 * res3;
//     }
//     string bnr3 = convertToBinary(res3);
//     int exp3 = normalizeBinary(bnr3);
//     if (exp3 + 3 > 7) {
//         exp3 = 3;
//     }
//     string mantes3;

//     for (int i = 0; i < bnr3.length(); i++) {
//         if (bnr3[i] == '.') {
//             mantes3 = bnr3.substr(i + 1, i + 3);
//             break;
//         }
//     }
//     while (mantes3.length() < 4) {
//         mantes3 = mantes3 += '0';
//     }
//     string finalbnr = sgn3 + bitset<3>(exp3 + 4).to_string() + mantes3;
//     stringstream ss;
//     ss << uppercase << hex << stoi(finalbnr, nullptr, 2);
//     string hex = ss.str();
//     Regs.SetValues(hex , regIdxR);
// }
    
//    #include <iostream>
// #include <iomanip>
// #include <stdint.h>
// uint8_t rotateRight(Registers & Regs) {
//     const int bits = 8;
//     int steps = stoi(HextoDec(Input.subtr(2,2)));
//     uint8_t value= stoi(HextoDec(Regs.GetValues(Input.subtr(1,1))));
//     steps = steps % bits; 
//    uint8_t result= (value >> steps) | (value << (bits - steps));
//    Regs.SetValue(to_string(DectoHex(result)) , HexToDec(Input.subtr(1,1)));


// }

// int main() {
// }



