#include "ALU.h"
#include "Memory.h"
#include "Registers.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <string>
#include <fstream>
#include <istream>
#include <regex>
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