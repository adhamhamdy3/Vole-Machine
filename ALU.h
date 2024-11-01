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
    static bool isValid(const string&);
    int hexToTwosComplement(const string&);
    string decimalToHexTwosComplement(int value);
//--------------------------------------------------------
    float  hexToFloat(const string& );
    string floatToHex(float value);

};


#endif //VOLE_MACHINE_ALU_H
