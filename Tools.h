//
// Created by power on 10/6/2024.
//

#ifndef VOLE_MACHINE_TOOLS_H
#define VOLE_MACHINE_TOOLS_H
#include <sstream>
#include <string>
using namespace std;

class Tools {
public:
    static short hexToDec(const string&);
    static double hexToDecFloat(const string& hexValue);
    static string decToHex(int decimalValue);
    static string decToHexFloat(double decimalValue);
};


#endif //VOLE_MACHINE_TOOLS_H
