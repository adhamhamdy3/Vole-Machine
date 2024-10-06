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
