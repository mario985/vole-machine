#ifndef ALU_h
#define ALU_h
#include <iostream>
using namespace std;
class ALU {
public:
    int HexToDec(const string& number);
    string DecToHex(const string& decimal);
    double binaryFractionToDecimal(const string& binaryFraction);
    string decimalToBinary(int integerPart, bool isNegative, bool ch);
    string fractionalToBinary(double fractionalPart);
    string convertToBinary(double number);
    int normalizeBinary(string& binary);
};
#endif
