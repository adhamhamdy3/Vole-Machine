#ifndef VOLE_MACHINE_UTILITIES_H
#define VOLE_MACHINE_UTILITIES_H
#include <string>

using namespace std;

namespace Utilities {
    class Validations {
    public:
        static bool isValid(const  string& instruction);
        static bool isValid_memAddress(const  string& _memAddress);
        static bool isValid_regAddress(const char& _regAddress);
        static bool isHexChar(const char& hx);
        static bool isValidMemoryCellValue(const  string& cellValue);
        static bool isHex(const  string&);
        static bool isInt(const  string&);
    };

    class Conversions {
    public:
        static float hexToFloat(const  string&);
        static  string strToASCII(const  string& str);
        static  string ASCII_Char_toStr(char& ASCII_Char);
        static int hexToDec(const  string& HEX);
        static  string decToHex(const int INT);
        static  string intToBin(int INT);
        static  string fractionToBin(double frac, int perc = 8);
        static  string decToBin(double DEC);
        static double binToFloat(const  string& BIN);
        static void toUpper( string& str);
        static  string floatToBin(double DEC);
        static int hexToTwosComplementInt(const  string& HEX);
    };
}

#endif //VOLE_MACHINE_UTILITIES_H
