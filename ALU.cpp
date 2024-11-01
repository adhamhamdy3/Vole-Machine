#include "ALU.h"

short ALU::hexToDec(const string &hexValue) {
    short decimalValue;
    stringstream ss;

    ss << hex << hexValue;

    ss >> decimalValue;

    return decimalValue;
}
string ALU::decToHex(int decimalValue) {
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
string ALU::decToHexFloat(double decimalValue) {
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
double ALU::hexToDecFloat(const string& hexValue) {
    // Split the hexadecimal string into integer and fractional parts
    size_t pointPos = hexValue.find('.');

    // If there's no decimal point, assume no fractional part
    string intPartStr = (pointPos == string::npos) ? hexValue : hexValue.substr(0, pointPos);
    string fracPartStr = (pointPos == string::npos) ? "" : hexValue.substr(pointPos + 1);

    // Convert the integer part from hex to decimal
    int intPart = 0;
    for (char hexDigit: intPartStr) {
        intPart = intPart * 16 + (isdigit(hexDigit) ? hexDigit - '0' : toupper(hexDigit) - 'A' + 10);
    }

    // Convert the fractional part from hex to decimal
    double fracPart = 0.0;
    double base = 1.0 / 16.0;
    for (char hexDigit: fracPartStr) {
        int decimalDigit = isdigit(hexDigit) ? hexDigit - '0' : toupper(hexDigit) - 'A' + 10;
        fracPart += decimalDigit * base;
        base /= 16.0;
    }

    // Combine the integer and fractional parts
    return intPart + fracPart;
}

bool ALU::isHex(const string &HEX) {
    if (HEX.empty()) return false;

    for (char ch : HEX) {
        if (!std::isxdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}

bool ALU::isValid(const string &ir) {
    if (ir.length() != 4 or !ALU::isHex(ir.substr(1)) or ALU::containsLowerCaseHex(ir))
        return false;

    short memoryCell, register_idx1, register_idx2, register_idx3;
    bool check1, check2, check3;

    if (ir[0] == '1' or ir[0]=='3') {
        register_idx1 = ALU::hexToDec(string(1, ir[1]));
        memoryCell = ALU::hexToDec(ir.substr(2));

        if (!ALU::isValidRegIdx(register_idx1) or !ALU::isValidMemIdx(memoryCell))
            return false;

    } else if (ir[0] == '2') {
        register_idx1 = ALU::hexToDec(string(1, ir[1]));

        if (!ALU::isValidRegIdx(register_idx1))
            return false;
    } else if (ir[0] == '4') {
        if (ir[1] != '0') return false;

        register_idx2 = ALU::hexToDec(string(1, ir[2]));
        register_idx3 = ALU::hexToDec(string(1, ir[3]));

        check1 = ALU::isValidRegIdx(register_idx2);
        check2 = ALU::isValidRegIdx(register_idx3);

        if (!check1 or !check2)
            return false;
    }


    else if (ir[0] == '5' or ir[0] == '6') {
        register_idx1 = ALU::hexToDec(string(1, ir[1]));
        register_idx2 = ALU::hexToDec(string(1, ir[2]));
        register_idx3 = ALU::hexToDec(string(1, ir[3]));

        check1 = ALU::isValidRegIdx(register_idx1);
        check2 = ALU::isValidRegIdx(register_idx2);
        check3 = ALU::isValidRegIdx(register_idx3);

        if (!check1 or !check2 or !check3)
            return false;

    } else if (ir[0] == 'B') {
        short register_idx1 = ALU::hexToDec(string(1, ir[1]));

        if (!ALU::isValidRegIdx(register_idx1))
            return false;

    } else if (ir[0] == 'C') {
        if (ir != "C000")
            return false;
    } else
        return false;

    return true;
}

bool ALU::containsLowerCaseHex(const string &hexStr) {
    return false;
}

bool ALU::isValidRegIdx(const short &regIdx) {
    return regIdx >= 0 and regIdx < 16;
}

bool ALU::isValidMemIdx(const short &memIdx) {
    return memIdx >= 0 and memIdx < 256;
}
void ALU::upperInstruction( string& upper) {

    for (int i = 0; i < upper.size(); i++) {
        if (upper[i] >= 'a' and upper[i] <= 'f')upper[i] = toupper(upper[i]);
    }
}
