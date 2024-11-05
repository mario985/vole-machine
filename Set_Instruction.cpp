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
void Set_Instruction::ChooseInstruction(string& input, Registers& Reg, Memory& Mem, int &ptr) {
    Input = input;
    char opCode = Input[0];
    if (opCode == '1' || opCode == '2') {
        Load(Reg, Mem);
    }
    else if (opCode == '3') {
        if (Input[2] == '0' && Input[3] == '0') { 
            Store(Reg, Mem);
            output(Reg); 
        }
        else Store(Reg, Mem);
    }
    else if (opCode == '4') {
        Move(Reg);
    }
    else if (opCode == '5') {
        twosCompAdd(Reg);
    }
    else if (opCode == '6') {
        FloatAdd(Reg);
    }
    else if (opCode == '7') {
        BitOR(Reg);
    }
    else if (opCode == '8') {
        BitAND(Reg);
    }
    else if (opCode == '9') {
        BitXOR(Reg);
    }
    else if (opCode == 'A') {
        rotateRight(Reg);
    }
    else if (opCode == 'B' && Jump(Reg)) {
        ptr = HexToDec(Input.substr(2, 2)) - 2;
        input.clear();
        return;
    }
    else if (opCode == 'C') {
        return;
    }
    else if (opCode == 'D' && Jump2(Reg)) {
        ptr = HexToDec(Input.substr(2, 2));
        input.clear();
        return;
    }
    input.clear();

}
void Set_Instruction::Load(Registers& Regs, Memory& Mem) {
    char operation = Input[0];
    int regIdx = HexToDec(Input.substr(1, 1));
    int memAddr = HexToDec(Input.substr(2, 2));

    if (operation == '1') {
        Regs.SetValues(Mem.Get_Value(memAddr), regIdx);
    }
    else {
        cout<<"Load "<<regIdx<<"With "<<memAddr<<" Bits"<<endl;
        Regs.SetValues(Input.substr(2, 2), regIdx); // Load immediate value
    }
}

void Set_Instruction::Store(Registers& Regs, Memory& Mem) {
    int regIdx = HexToDec(Input.substr(1, 1));
    int memAddr = HexToDec(Input.substr(2, 2));
    Mem.Set_Value(Regs.GetValues(regIdx), memAddr);
}

void Set_Instruction::Move(Registers& Regs) {
    int regSrc = HexToDec(Input.substr(2, 1));
    int regDest = HexToDec(Input.substr(3, 1));
    Regs.SetValues(Regs.GetValues(regSrc), regDest);
}

bool Set_Instruction::Jump(Registers& Regs) {
    int regIdx = HexToDec(Input.substr(1, 1));
    return Regs.GetValues(regIdx) == Regs.GetValues(0);
}
void Set_Instruction::twosCompAdd(Registers &R) {

    int regIdxR = HexToDec(Input.substr(1, 1)); // index of reg to store bits at
    int regIdxS = HexToDec(Input.substr(2, 1)); // index of reg1 to add
    int regIdxT = HexToDec(Input.substr(3, 1)); // index of reg2 to add
    string value1 = "0x";
    string value2 = "0x";
    value1 += R.GetValues(regIdxS); // Hexa form of the value in the register
    value2 += R.GetValues(regIdxT);
    int num1 = stoi(value1, nullptr, 16) - 256; // adjust the 2 numbers in 2's Comp by subtracting 256
    int num2 = stoi(value2, nullptr, 16) - 256;
    int res = num1 + num2;
    string result = DecToHex(to_string(res));
    result = result.substr(6,2);
    R.SetValues(result, regIdxR);
}
void Set_Instruction::BitOR(Registers& Regs) {
    int regIdxR = HexToDec(Input.substr(1, 1)); // index of reg to store bits at
    int regIdxS = HexToDec(Input.substr(2, 1)); // index of reg1 to add
    int regIdxT = HexToDec(Input.substr(3, 1)); // index of reg2 to add
    string value1 = "0x";
    string value2 = "0x";
    /*
    2001
    2121
    7201
    */
    value1 += Regs.GetValues(regIdxS); // Hexa form of the value in the register
    value2 += Regs.GetValues(regIdxT);
    int num1 = stoi(value1, nullptr, 16);
    int num2 = stoi(value2, nullptr, 16);
    int result = (num1 | num2);
    string res = DecToHex(to_string(result));
    if (res.length() == 1) {
        res.insert(0, "0");
    }
    Regs.SetValues(res, regIdxR);

}
void Set_Instruction::BitAND(Registers& Regs) {
    int regIdxR = HexToDec(Input.substr(1, 1)); // index of reg to store bits at
    int regIdxS = HexToDec(Input.substr(2, 1)); // index of reg1 to add
    int regIdxT = HexToDec(Input.substr(3, 1)); // index of reg2 to add
    string value1 = "0x";
    string value2 = "0x";
    /*
    2001
    2121
    7201
    */
    value1 += Regs.GetValues(regIdxS); // Hexa form of the value in the register
    value2 += Regs.GetValues(regIdxT);
    int num1 = stoi(value1, nullptr, 16);
    int num2 = stoi(value2, nullptr, 16);
    int result = (num1 & num2);
    string res = DecToHex(to_string(result));
    if (res.length() == 1) {
        res.insert(0, "0");
    }
    Regs.SetValues(res, regIdxR);
}
void Set_Instruction::BitXOR(Registers& Regs) {
    int regIdxR = HexToDec(Input.substr(1, 1)); // index of reg to store bits at
    int regIdxS = HexToDec(Input.substr(2, 1)); // index of reg1 to add
    int regIdxT = HexToDec(Input.substr(3, 1)); // index of reg2 to add
    string value1 = "0x";
    string value2 = "0x";
    /*
    2001
    2121
    7201
    */
    value1 += Regs.GetValues(regIdxS); // Hexa form of the value in the register
    value2 += Regs.GetValues(regIdxT);
    int num1 = stoi(value1, nullptr, 16);
    int num2 = stoi(value2, nullptr, 16);
    int result = (num1 ^ num2);
    string res = DecToHex(to_string(result));
    if (res.length() == 1) {
        res.insert(0, "0");
    }
    Regs.SetValues(res, regIdxR);
}
void Set_Instruction::output(Registers& R){
    int regIdxR = HexToDec(Input.substr(1, 1));
    string hexstr = "0x";
    hexstr += R.GetValues(regIdxR);
    int AsciiVal = stoi(hexstr, nullptr, 16);
    outputstr += char(AsciiVal);
}

bool Set_Instruction::Compare(Registers& R) {
    int regIdxS = HexToDec(Input.substr(1, 1)); // index of reg1 to add
    int regIdxT = 0;// index of reg2 to add
    string value1 = R.GetValues(regIdxS); // Hexa form of the value in the register
    string value2 = R.GetValues(regIdxT);
    int num1 = stoi(value1, nullptr, 16) - 256; // adjust the 2 numbers in 2's Comp by subtracting 256
    int num2 = stoi(value2, nullptr, 16) - 256;
    return num1 > num2;
}
bool Set_Instruction::Jump2(Registers& Regs) {
    int regIdx = HexToDec(Input.substr(1, 1));
    return Compare(Regs);
}
void Set_Instruction::FloatAdd(Registers& Regs) {
    int regIdxR = HexToDec(Input.substr(1, 1)); // index of reg to store bits at
    string H1 = Regs.GetValues(HexToDec(Input.substr(2, 1))); // index of reg1 to add
    string H2 = Regs.GetValues(HexToDec(Input.substr(3, 1))); // index of reg2 to add
    string bnr1 = bitset<8>(stoul(H1, nullptr, 16)).to_string();
    string bnr2 = bitset<8>(stoul(H2, nullptr, 16)).to_string();
    int sgn1 = stoi(bnr1.substr(0, 1));
    int sgn2 = stoi(bnr2.substr(0, 1));
    int exp1 = bitset<8>(bnr1.substr(1, 3)).to_ulong();
    int exp2 = bitset<8>(bnr2.substr(1, 3)).to_ulong();
    string mantesa1 = "0." + bnr1.substr(4, 8);
    double man1 = binaryFractionToDecimal(mantesa1);
    string mantesa2 = "0." + bnr2.substr(4, 8);
    double man2 = binaryFractionToDecimal(mantesa2);
    double res1 = pow(-1, sgn1) * pow(2, exp1 - 4) * double(1 + man1);
    double res2 = pow(-1, sgn2) * pow(2, exp2 - 4) * double(1 + man2);
    double res3 = res1 + res2;
    string sgn3 = "0";
    if ((res3 < 0)) {
        sgn3 = '1';
        res3 = -1 * res3;
    }
    string bnr3 = convertToBinary(res3);
    int exp3 = normalizeBinary(bnr3);
    if (exp3 + 3 > 7) {
        exp3 = 3;
    }
    string mantes3;

    for (int i = 0; i < bnr3.length(); i++) {
        if (bnr3[i] == '.') {
            mantes3 = bnr3.substr(i + 1, i + 3);
            break;
        }
    }
    while (mantes3.length() < 4) {
        mantes3 = mantes3 += '0';
    }
    string finalbnr = sgn3 + bitset<3>(exp3 + 4).to_string() + mantes3;
    stringstream ss;
    ss << uppercase << hex << stoi(finalbnr, nullptr, 2);
    string hex = ss.str();
    Regs.SetValues(hex, regIdxR);
}
void Set_Instruction::rotateRight(Registers& Regs) {
    const int bits = 8;
    int steps = HexToDec(Input.substr(2, 2));
    uint8_t value = HexToDec(Regs.GetValues(stoi(Input.substr(1, 1))));
    steps = steps % bits;
    uint8_t result1 = (value >> steps) | (value << (bits - steps));
    //    int result= static_cast<int>(result1);
    string result = (DecToHex(to_string(result1)));
    if (result.length() == 1) {
        result.insert(0, "0");
    }
    Regs.SetValues(result, HexToDec(Input.substr(1, 1)));



}
