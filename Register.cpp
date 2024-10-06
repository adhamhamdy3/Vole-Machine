//
// Created by Adham Hamdy on 10/4/2024.
//

#include "Register.h"

Register::Register(const string &val) : value{val} {

}

Register::~Register() {

}

void Register::setValue(const string &val) {
    value = val;
}

const string &Register::getValue() const {
    return value;
}

void Register::clear(const int &index) {

}
