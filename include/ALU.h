#ifndef VOLE_MACHINE_ALU_H
#define VOLE_MACHINE_ALU_H

#include <sstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <bitset>
#include <limits>
using namespace std;

class ALU {
private:
    static bool isValidRegIdx(const short&);
    static bool isValidMemIdx(const short&);
public:
    static bool isHex(const string&);
    static short hexToDec(const string&);
    static bool isValid(const string&);
    static void upperInstruction(string&);
    int hexToTwosComplement(const string&);
    string decimalToHexTwosComplement(int value);
    static float  hexToFloat(const string&);
    string floatToHex(float value);
    double hexToDecFloat(const string& hexValue);
    static string decToHex(int decimalValue);
    string decToHexFloat(double decimalValue);
    static bool isInt(const string&);

};


#endif //VOLE_MACHINE_ALU_H
