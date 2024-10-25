//
// Created by power on 10/6/2024.
//

#ifndef VOLE_MACHINE_ALU_H
#define VOLE_MACHINE_ALU_H
#include <sstream>
using namespace std;

class ALU {
public:
    static short hexToDec(const string&);
    static double hexToDecFloat(const string& hexValue);
    static string decToHex(int decimalValue);
    static string decToHexFloat(double decimalValue);
};


#endif //VOLE_MACHINE_ALU_H
