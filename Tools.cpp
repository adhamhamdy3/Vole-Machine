//
// Created by power on 10/6/2024.
//

#include "Tools.h"

short Tools::hexToDec(const string &hexValue) {
    short decimalValue;
    stringstream ss;

    ss << hex << hexValue;

    ss >> decimalValue;

    return decimalValue;
}
string Tools::decToHex(int decimalValue) {
    if (decimalValue == 0)
        return "0";

    string hex;
    char hexDigits[] = "0123456789ABCDEF";

    while (decimalValue > 0) {
        int remainder = decimalValue % 16;
        hex = hexDigits[remainder] + hex;  // Prepend the corresponding hex digit
        decimalValue /= 16;
    }

    return hex;
}
//============
string Tools::decToHexFloat(double decimalValue) {
    if (decimalValue == 0.0)
        return "0.0";

    string hex;
    char hexDigits[] = "0123456789ABCDEF";

    // Separate the integer and fractional parts
    int intPart = static_cast<int>(decimalValue);
    double fracPart = decimalValue - intPart;

    // Convert the integer part to hexadecimal
    string intHex;
    while (intPart > 0) {
        int remainder = intPart % 16;
        intHex = hexDigits[remainder] + intHex;
        intPart /= 16;
    }

    // Convert the fractional part to hexadecimal
    string fracHex;
    int precision = 6;  // Set precision for fractional part to prevent infinite loop
    while (fracPart > 0 && precision > 0) {
        fracPart *= 16;
        int fracInt = static_cast<int>(fracPart);
        fracHex += hexDigits[fracInt];
        fracPart -= fracInt;
        precision--;
    }

    // Combine integer and fractional parts
    hex = intHex + "." + (fracHex.empty() ? "0" : fracHex);

    return hex;
}

// function to convert hexadecimal floating-point to decimal floating-point
double Tools::hexToDecFloat(const string& hexValue) {
    // Split the hexadecimal string into integer and fractional parts
    size_t pointPos = hexValue.find('.');

    // If there's no decimal point, assume no fractional part
    string intPartStr = (pointPos == string::npos) ? hexValue : hexValue.substr(0, pointPos);
    string fracPartStr = (pointPos == string::npos) ? "" : hexValue.substr(pointPos + 1);

    // Convert the integer part from hex to decimal
    int intPart = 0;
    for (char hexDigit : intPartStr) {
        intPart = intPart * 16 + (isdigit(hexDigit) ? hexDigit - '0' : toupper(hexDigit) - 'A' + 10);
    }

    // Convert the fractional part from hex to decimal
    double fracPart = 0.0;
    double base = 1.0 / 16.0;
    for (char hexDigit : fracPartStr) {
        int decimalDigit = isdigit(hexDigit) ? hexDigit - '0' : toupper(hexDigit) - 'A' + 10;
        fracPart += decimalDigit * base;
        base /= 16.0;
    }

    // Combine the integer and fractional parts
    return intPart + fracPart;
}
