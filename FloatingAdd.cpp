#include <iostream>
#include <string>
#include <bitset>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;
double binaryFractionToDecimal(const string& binaryFraction) {
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
string decimalToBinary(int integerPart, bool isNegative, bool ch) {
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

string fractionalToBinary(double fractionalPart) {
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

string convertToBinary(double number) {
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
int normalizeBinary(string& binary) {
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
            exponent = (decimalPos - firstOne);
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
}
string decimalToHex(int decimal) {
    stringstream ss;
    ss << hex << uppercase << decimal;
    return ss.str();
}
void FloatAdd(string H1, string H2) {
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
    cout << hex << " ";



}
int main() {
    FloatAdd("A", "A");
}
