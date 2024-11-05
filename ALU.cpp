#include "ALU.h"
#include "Memory.h"
#include "Registers.h"
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;
int ALU::HexToDec(const string& hex) {
    return stoi(hex, nullptr, 16);

}
string ALU::DecToHex(const string& decimal) {
    int decimalNumber;
    std::stringstream ss;

    // Convert the string to an integer
    ss << decimal;
    ss >> decimalNumber;

    // Clear the stringstream and set to hex mode
    ss.clear();
    ss.str("");

    // Set uppercase and hex mode
    ss << std::uppercase << std::hex << decimalNumber;

    // Return the hex string
    return ss.str();
}
double ALU::binaryFractionToDecimal(const string& binaryFraction) {
    double decimalValue = 0.0;
    size_t pointPosition = binaryFraction.find('.');
    if (pointPosition == string::npos) {
        return 0.0;
    }
    for (size_t i = pointPosition + 1; i < binaryFraction.size(); ++i) {
        if (binaryFraction[i] == '1') {
            decimalValue += 1.0 / pow(2, i - pointPosition);
        }
    }
    return decimalValue;
}
string ALU::decimalToBinary(int integerPart, bool isNegative, bool ch) {
    if (!ch) {
        return "0";
    }
    string binary = "";
    if (isNegative) {
        integerPart = (1 << 4) + integerPart;
    }

    if (integerPart == 0) {
        return "0000";
    }
    while (integerPart > 0) {
        binary = to_string(integerPart % 2) + binary;
        integerPart /= 2;
    }
    while (binary.length() < 4) {
        binary = "0" + binary;
    }
    if (!isNegative && binary.length() > 8) {
        string binary8 = string(8 - binary.length(), '0') + binary;
        return binary8;
    }
    return binary;
}

string ALU::fractionalToBinary(double fractionalPart) {
    string binary = ".";
    int count = 0;

    while (fractionalPart > 0 && count < 8) {
        fractionalPart *= 2;
        if (fractionalPart >= 1) {
            binary += "1";
            fractionalPart -= 1;
        }
        else {
            binary += "0";
        }
        count++;
    }

    return binary;
}

string ALU::convertToBinary(double number) {
    string binary;
    bool isNegative = number < 0;
    if (isNegative) {
        number = -number;
    }
    int integerPart = static_cast<int>(number);
    double fractionalPart = number - integerPart;
    bool check = 0;
    if (integerPart) {
        check = 1;
    }
    binary += decimalToBinary(integerPart, isNegative, check);

    if (fractionalPart > 0) {
        binary += fractionalToBinary(fractionalPart);
    }

    return binary;
}
int ALU::normalizeBinary(string& binary) {
    size_t exponent = 0;
    string normalized;
    // Find the position of the first '1'
    size_t firstOne = binary.find('1');
    if (binary.length() == 1 && binary[0] == '0') {
        firstOne = 0;
    }
    if (binary.find('.') != string::npos) {
        // Case when there is a decimal point in the binary string
        size_t decimalPos = binary.find('.');
        if (firstOne < decimalPos) {
            // Example: 0.1101 -> 1.101 * 2^-1
            exponent = -1 * (decimalPos - firstOne);
        }
        else {
            // Example: 1.101 -> already normalized
            exponent = firstOne - decimalPos;
        }
    }
    else {
        // Case when it's a binary integer (e.g., 00111110)
        exponent = binary.length() - firstOne - 1;
    }
    // Move the first `1` to the start, and insert a decimal point
    normalized = binary.substr(firstOne, binary.length() - firstOne);
    normalized.insert(1, ".");
    if (binary[1] == '.') {
        exponent *= -1;
    }
    binary = normalized;
    return (int)exponent;
<<<<<<< HEAD
}
=======
}
>>>>>>> ccb3b64d80a319ab1d95b8035a67d9771c43620a
