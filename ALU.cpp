#include "ALU.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <string>
using namespace std;
int ALU::HexToDec(const string&hex){
    return stoi(hex, nullptr , 16);

}
string ALU::DecToHex(const string & decimal){
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
bool ALU::Is_Valid(const string& number) {
    if (number.empty()) return false; // Add this line to avoid accessing number[0]
    char firstChar = number[0];
    // Check if the first character is a digit and within the valid range
    if (isdigit(firstChar)) {
        int intValue = firstChar - '0'; // Convert char to integer
        return (intValue > 0 && intValue <= 5);
    }
    // Check if the first character is 'B' or 'C'
    return (toupper(firstChar) == 'B' || toupper(firstChar) == 'C');
}
