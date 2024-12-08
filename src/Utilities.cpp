#include "Utilities.h"
#include <algorithm>
#include <sstream>
#include <cmath>
#include <string>
#include <stdexcept>
#include <bitset>
using namespace Utilities;

float Conversions::hexToFloat(const std::string& hex){
    if (hex.length() != 2) {
        throw std::invalid_argument("Hexadecimal string must be 2 characters long.");
    }


    unsigned int value = stoul(hex, nullptr, 16);


    std::bitset<8> bits(value);

    int sign = bits[7];

    int exponent = (bits[6] << 2) | (bits[5] << 1) | bits[4];

    int mantissa = (bits[3] << 3) | (bits[2] << 2) | (bits[1] << 1) | bits[0];

    int actualExponent = static_cast<int>(exponent) - 4;

    if (exponent == 0) {
        return 0.0;
    }
    float normalizedMantissa = 0.0;

    for (int i = 3; i >= 0; --i) {

        int bit = mantissa / static_cast<int>(pow(2, i)) % 2;


        if (bit == 1) {
            normalizedMantissa += pow(2, -(4 - i));
        }
    }





    float floatValue = pow(-1, sign) * normalizedMantissa * pow(2.0, actualExponent);


    return floatValue;
}

bool Validations::isHex(const std::string &HEX){
    if (HEX.empty()) return false;

    for (char ch : HEX) {
        if (!isxdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}

bool Validations::isInt(const std::string &INT){
    if(INT.empty()) return false;

    for(const char& x : INT){
        if(!isdigit(x))
            return false;
    }
    return true;
}

bool Validations::isValid(const std::string& instruction) {
    if (instruction.size() != 4) {
        return false;
    }

    char opcode = toupper(instruction[0]);

    if ((opcode >= '1' && opcode <= '3') || opcode == 'B' || opcode == 'D') {
        return isValid_regAddress(instruction[1]) &&
               isValid_memAddress(instruction.substr(2));
    }

    if (opcode == '4') {
        return isValid_regAddress(instruction[2]) &&
               isValid_regAddress(instruction[3]);
    }

    if (opcode >= '5' && opcode <= '9') {
        return isValid_regAddress(instruction[1]) &&
               isValid_regAddress(instruction[2]) &&
               isValid_regAddress(instruction[3]);
    }

    if (opcode == 'A') {
        return isValid_regAddress(instruction[1]) &&
               isHexChar(instruction[3]);
    }

    if (opcode == 'C') {
        return true;
    }

    return false;
}

bool Validations::isValid_memAddress(const std::string& _memAddress) {
    if (_memAddress.size() != 2) {
        return false;
    }

    return isHexChar(_memAddress[0]) && isHexChar(_memAddress[1]);
}

bool Validations::isValid_regAddress(const char& _regAddress) {
    return (_regAddress >= '0' && _regAddress <= '9') || (toupper(_regAddress) >= 'A' && toupper(_regAddress) <= 'F');
}

bool Validations::isHexChar(const char& hx) {
    return (hx >= '0' && hx <= '9') || (toupper(hx) >= 'A' && toupper(hx) <= 'F');
}

bool Utilities::Validations::isValidMemoryCellValue(const std::string& cellValue) {
    if (cellValue.size() == 2) {
        return isHexChar(cellValue[0]) && isHexChar(cellValue[1]);
    }

    if (cellValue.size() == 1) {
        return isHexChar(cellValue[0]);
    }

    if (cellValue.size() == 0) {
        return true;
    }

    return false;
}



std::string Utilities::Conversions::strToASCII(const string &str) {
    int ASCII = hexToDec(str);
    char char_result = char(ASCII);
    std::string result = "";
    result.push_back(char_result);
    return result;
}

std::string Utilities::Conversions::ASCII_Char_toStr(char& ASCII_Char) {
    int ASCII = int(ASCII_Char);
    std::string result = Conversions::decToHex(ASCII);
    return result;
}


int Conversions::hexToDec(const std::string& HEX) {
    int decimalValue = std::stoi(HEX, nullptr, 16);
    return decimalValue;
}


std::string Conversions::decToHex(const int INT) {
    std::stringstream stream;
    stream << std::hex << (INT & 0xFF);
    std::string result = stream.str();
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);

    return result;
}

std::string Conversions::intToBin(int INT) {
    const int BITS = 8;
    std::string binary;

    // Handle two's complement for negative integers
    if (INT < 0) {
        INT += (1 << BITS); // Convert to unsigned equivalent
    }

    while (INT > 0) {
        binary = std::to_string(INT % 2) + binary;
        INT /= 2;
    }

    // Pad with leading zeros to ensure BITS width
    while (binary.size() < BITS) {
        binary = "0" + binary;
    }

    return binary;
}


std::string Conversions::fractionToBin(double frac, int perc) {
    std::string binFraction = ".";
    while (frac > 0 && perc-- > 0) {
        frac *= 2;
        if (frac >= 1) {
            binFraction += "1";
            frac -= 1;
        }
        else {
            binFraction += "0";
        }
    }
    return binFraction;
}


std::string Conversions::decToBin(double DEC) {
    int integer = int(DEC);
    double fraction = DEC - integer;

    std::string binary = Conversions::intToBin(integer) + Conversions::fractionToBin(fraction);
    return binary;
}



double Conversions::binToFloat(const std::string& BIN) {
    std::string binary = std::string(8 - BIN.size(), '0') + BIN;

    int sign = (binary[0] == '0') ? 1 : -1;
    int exponent = (binary[1] - '0') * 4 + (binary[2] - '0') * 2 + (binary[3] - '0');
    double mantissa = (binary[4] - '0') * 0.5 +
                      (binary[5] - '0') * 0.25 +
                      (binary[6] - '0') * 0.125 +
                      (binary[7] - '0') * 0.0625;

    const int BIAS = 4;
    double result = sign * mantissa * std::pow(2, exponent - BIAS);

    if (result > 7.5) {
        result = 7.5;
    } else if (result < -7.5) {
        result = -7.5;
    }

    return result;
}




void Utilities::Conversions::toUpper(std::string& str) {
    for (char& ch : str) {
        ch = toupper(ch);
    }
}

std::string Conversions::floatToBin(double DEC) {
    char sign_bit = (DEC >= 0) ? '0' : '1';

    std::string normal_binary = Conversions::decToBin(std::abs(DEC));
    int radix_point_position = normal_binary.find('.');
    int significant_bit_position = normal_binary.find('1');

    int exponent = (radix_point_position > significant_bit_position)
                   ? (radix_point_position - significant_bit_position)
                   : (radix_point_position - significant_bit_position + 1);

    const int BIAS = 4;
    std::string exponent_bits = Conversions::intToBin(exponent + BIAS);
    exponent_bits.insert(0, 3 - exponent_bits.size(), '0');

    std::string mantissa_bits;
    for (size_t i = significant_bit_position + 1; i < normal_binary.size() && mantissa_bits.size() < 4; ++i) {
        if (normal_binary[i] != '.') {
            mantissa_bits.push_back(normal_binary[i]);
        }
    }
    mantissa_bits.insert(mantissa_bits.end(), 4 - mantissa_bits.size(), '0');

    return sign_bit + exponent_bits + mantissa_bits;
}


int Conversions::hexToTwosComplementInt(const std::string& HEX) {
    int DEC = Conversions::hexToDec(HEX);

    std::string BIN = Conversions::intToBin(DEC);
    BIN.insert(0, 8 - BIN.size(), '0');

    if (BIN[0] == '1') {
        for (char& bit : BIN) {
            bit = (bit == '0') ? '1' : '0';
        }
        int invertedValue = std::stoi(BIN, nullptr, 2);
        return -(invertedValue + 1);
    }

    return std::stoi(BIN, nullptr, 2);
}
