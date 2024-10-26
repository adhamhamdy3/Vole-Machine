#ifndef VOLE_MACHINE_ALU_H
#define VOLE_MACHINE_ALU_H

#include <sstream>
using namespace std;

class ALU {
public:
    short hexToDec(const string&);
    double hexToDecFloat(const string& hexValue);
    string decToHex(int decimalValue);
    string decToHexFloat(double decimalValue);
};


#endif //VOLE_MACHINE_ALU_H
