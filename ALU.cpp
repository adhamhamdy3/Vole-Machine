#include "ALU.h"

short ALU::hexToDec(const string &hexValue) {
    short decimalValue;
    stringstream ss;

    ss << hex << hexValue;

    ss >> decimalValue;

    return decimalValue;
}

//============
int ALU ::hexToTwosComplement(const string& hexVal) {

    unsigned int value;
    stringstream ss;
    ss << hex << hexVal;
    ss >> value;


    if (value & 10000000) {

        return static_cast<int>(value - 256);
    } else {

        return static_cast<int>(value);
    }
}

//===========================================

string ALU::decimalToHexTwosComplement(int value) {


    int maxValue = 1 << 8;
    if (value < 0) {
        value = maxValue + value;
    }

    stringstream ss;
    ss << hex << uppercase << setfill('0')
       << setw(8 / 4) << value;
    string hexval=ss.str();
    return hexval;
}


//=====================================================

float ALU:: hexToFloat(const string& hex) {
    if (hex.length() != 2) {
        throw invalid_argument("Hexadecimal string must be 2 characters long.");
    }


    unsigned int value = stoul(hex, nullptr,16);


    bitset<8> bits(value);

    int sign = bits[7];

    int exponent = (bits[6] << 2) | (bits[5] << 1) | bits[4];

    int mantissa = (bits[3] << 3) | (bits[2] << 2) | (bits[1] << 1) | bits[0];

    int actualExponent = static_cast<int>(exponent) - 4;

    if (exponent == 0) {
        return 0.0;
    }
    float normalizedMantissa=0.0;

    for (int i = 3; i >= 0; --i) {

        int bit = mantissa / static_cast<int>(pow(2, i)) % 2;


        if (bit == 1) {
            normalizedMantissa += pow(2, -(4 - i));
        }
    }





    float floatValue = pow(-1,sign) * normalizedMantissa * pow(2.0, actualExponent);


    return floatValue;
}

//===============================================
string ALU::floatToHex(float value) {

    if (value == 0.0) {
        return "00";
    }


    int sign = (value < 0) ? 1 : 0;


    float absValue = fabs(value);


    int exponent = 0;
    while (absValue >= 1.0) {
        absValue /= 2.0;
        exponent++;
    }
    while (absValue < 0.5) {
        absValue *= 2.0;
        exponent--;
    }


    const int bias = 4;
    int exponentBiased = exponent + bias;


    if (exponentBiased < 0 || exponentBiased >= 8) {
        throw std::invalid_argument("Exponent out of range for 3 bits.");
    }


    int mantissa = static_cast<int>((absValue) * (1 << 4));


    if (mantissa < 0 || mantissa >= 16) {
        throw std::invalid_argument("Mantissa out of range for 4 bits.");
    }


    int hexValue = (sign << 7) | (exponentBiased << 4) | mantissa;


    stringstream stream;
    stream <<uppercase << hex << setw(2) << setfill('0') << hexValue;

    return stream.str();
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
