#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

// Function to convert a hex string to an integer, considering two's complement
int hex_to_twos_complement(const std::string& hexStr, int bitSize) {
    unsigned long value = std::stoul(hexStr, nullptr, 16);
    
    if (value >= (1UL << (bitSize - 1))) {
        value -= (1UL << bitSize); // Convert to negative two's complement
    }
    
    return static_cast<int>(value);
}

// Function to convert an integer back to hex string in two's complement format
std::string int_to_twos_complement_hex(int value, int bitSize) {
    unsigned int mask = (1U << bitSize) - 1; // Mask for bitSize
    unsigned int twosComplementValue = value & mask; // Apply the mask
    
    std::stringstream ss;
    ss << std::hex << std::uppercase << twosComplementValue; // Convert to hex string
    return ss.str();
}

// Function to add two hex numbers in two's complement
std::string add_hex_twos_complement(const std::string& hex1, const std::string& hex2) {
    // Determine bit size based on the longer of the two hex strings
    int bitSize = std::max(hex1.length(), hex2.length()) * 4;

    int num1 = hex_to_twos_complement(hex1, bitSize);
    int num2 = hex_to_twos_complement(hex2, bitSize);
    
    // Perform addition
    int result = num1 + num2;

    // Convert result back to hex in two's complement format
    return int_to_twos_complement_hex(result, bitSize);
}

int main() {
    std::string hex1 = "F";   // 1 digit
    std::string hex2 = "FF";  // 2 digits

    // Add the hex values in two's complement and get the result as a hex string
    std::string result = add_hex_twos_complement(hex1, hex2);

    // Output the result
    std::cout << "Result of adding " << hex1 << " and " << hex2 << " in two's complement: " << result << std::endl;

    return 0;
}
/*
// int Set_Instruction::hex_to_twos_complement(const string& hexStr, int bitSize){
//     unsigned long value = stoul(hexStr, nullptr, 16);
    
//     if (value >= (1UL << (bitSize - 1))) {
//         value -= (1UL << bitSize); // Convert to negative two's complement
//     }
    
//     return static_cast<int>(value);
// }

// // Function to convert an integer back to hex string in two's complement format
// string Set_Instruction::int_to_twos_complement_hex(int value, int bitSize) {
//     unsigned int mask = (1U << bitSize) - 1; // Mask for bitSize
//     unsigned int twosComplementValue = value & mask; // Apply the mask
    
//     std::stringstream ss;
//     ss <<hex <<uppercase << twosComplementValue; // Convert to hex string
//     return ss.str();

// }
// string Set_Instruction::add_hex_twos_complement(const string& hex1, const string& hex2){
//      int bitSize = std::max(hex1.length(), hex2.length()) * 4;

//     int num1 = hex_to_twos_complement(hex1, bitSize);
//     int num2 = hex_to_twos_complement(hex2, bitSize);
    
//     // Perform addition
//     int result = num1 + num2;

//     // Convert result back to hex in two's complement format
//     return int_to_twos_complement_hex(result, bitSize);
// }
// void Set_Instruction::Add_TwosComplement(Registers & Reg){//5657 == R6 = R5+R7
//     string reg1Index , resultIndex , reg2Index; 
//     reg1Index=Input[2] , reg2Index=Input[3] , resultIndex=Input[1];
//     string hex1 = int_to_twos_complement_hex(Reg.GetValue(stoi(reg1Index)), 8); // Assuming 8 bits
//     string hex2 = int_to_twos_complement_hex(Reg.GetValue(stoi(regIndex)), 8); // Assuming 8 bits
//     // Perform addition in two's complement and get result in hex
//     std::string resultHex = add_hex_twos_complement(hex1, hex2);
//     // Convert the resulting hex string back to integer to store it
//     int resultValue = hex_to_twos_complement(resultHex, 8); // Assuming 8 bits
//     Reg.SetValues(resultValue, resultIndex);
// }


*/