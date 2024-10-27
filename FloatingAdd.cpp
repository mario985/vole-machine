#include <iostream>
#include <string>
#include <bitset>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std ;
double binaryFractionToDecimal(const string& binaryFraction) {
    double decimalValue = 0.0;
    int pointPosition = binaryFraction.find('.');
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
string decimalToBinary(int integerPart , bool ch) {
    if (!ch){
        return "0" ;
    }
    string binary = "";
    if (integerPart == 0) {
        return "0000";
    }
    while (integerPart > 0) {
        binary = to_string(integerPart % 2) + binary;
        integerPart /= 2;
    }
    while (binary.length() < 4 && ch !=0) {
        binary = "0" + binary;
    }
    if (binary.length() > 4) {
        string binary8 = string(8 - binary.length(), '0') + binary;
        return binary8;
    }
    return binary;
}

string fractionalToBinary(double fractionalPart) {
    string binary = ".";
    int count = 0;
    while (fractionalPart > 0 && count < 4) {
        fractionalPart *= 2;
        if (fractionalPart >= 1) {
            binary += "1";
            fractionalPart -= 1;
        } else {
            binary += "0";
        }
        count++;
    }

    return binary;
}

string convertToBinary(double number) {
    string binary;
    int integerPart = static_cast<int>(number);
    double fractionalPart = number - integerPart;
    bool check = 0 ;
    if (integerPart){
        check = 1 ;
    }
    binary += decimalToBinary(integerPart , check);
    if (fractionalPart > 0) {
        binary += fractionalToBinary(fractionalPart);
    }

    return binary;
}
int normalizeBinary(string& binary) {
    int exponent = 0;
    string normalized;
    size_t firstOne = binary.find('1');
    
    if (firstOne == 0) {
        normalized = binary;
        exponent = binary.length() - 1;
    } else {
        normalized = binary.substr(firstOne, binary.length() - firstOne);
        exponent = firstOne - 1; 
        normalized.insert(1, ".");
    }
    if (binary[1] == '.'){
        exponent*=-1;
    }
    binary = normalized ;
    return exponent;
}

void FloatAdd (string H1 , string H2){
    string bnr1 = bitset<8>(stoul(H1, nullptr, 16)).to_string();
    string bnr2 = bitset<8>(stoul(H2, nullptr, 16)).to_string();
    int sgn1 = stoi(bnr1.substr(0,1));
    int sgn2 = stoi(bnr2.substr(0,1));
    int exp1 = bitset<8>(bnr1.substr(1,3)).to_ulong();
    int exp2 = bitset<8>(bnr2.substr(1,3)).to_ulong();
    string mantesa1 = "0."+bnr1.substr(4,8);
    double man1 = binaryFractionToDecimal(mantesa1);
    string mantesa2 = "0."+bnr2.substr(4,8);
    double man2 = binaryFractionToDecimal(mantesa2);
    double res1 = pow(-1,sgn1) * pow(2,exp1-3) * double(1+man1);
    double res2 = pow(-1,sgn2) * pow(2,exp2-3) * double(1+man2);
    string bnr3 = convertToBinary(res1+res2) ;
    int exp3 = normalizeBinary(bnr3) ;
    string mantes3 ;
    for (int i = 0 ; i < bnr3.length() ; i++ ){
        if (bnr3[i] == '.'){
            mantes3 = bnr3.substr(i+1 ,bnr3.length() );
            break;
        }
    }
    while (mantes3.length() < 4){
        mantes3 = mantes3 +='0';
    }
    string finalbnr = '0' + bitset<3>(exp3+3).to_string() + mantes3 ;
    stringstream ss; 
    ss << uppercase << hex << stoi(finalbnr, nullptr, 2); // Convert binary to integer, then to hex in uppercase
    string hex = ss.str(); // Get the hex string
    cout << hex ;

    

}
int main (){
    FloatAdd("5" , "15") ;
}