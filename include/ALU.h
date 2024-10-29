#ifndef VOLE_MACHINE_ALU_H
#define VOLE_MACHINE_ALU_H

#include <sstream>
using namespace std;

class ALU {
private:
    static bool containsLowerCaseHex(const string& hexStr);
    static bool isValidRegIdx(const short&);
    static bool isValidMemIdx(const short&);
public:
    static bool isHex(const string&);
    static short hexToDec(const string&);
    double hexToDecFloat(const string& hexValue);
    string decToHex(int decimalValue);
    string decToHexFloat(double decimalValue);
    static bool isValid(const string&);
    static bool isInt(const string&);

};


#endif //VOLE_MACHINE_ALU_H
