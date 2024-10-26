#include "Register.h"

Register::Register() {
    fill(registers, registers + 16, "00");
}

void Register::setCell(const int &address, const string &value) {
    try {
        if (address < 0 || address > 15)
            throw out_of_range("Out of range! address must be between [0-15].");
        //throw exception if the value is not valid
        registers[address] = value;
    } catch (const exception& e){
        cerr << "Error: " << e.what() << endl;
    }

}

string Register::getCell(const int &address) const {
    string value{"N/A"};
    try {
        if (address < 0 || address > 255)
            throw out_of_range("Out of range! address must be between [0-15].");
        value = registers[address];
    }
    catch (const exception& e) {
        cerr << "Error:" << e.what() << endl;
    }
    return value;
}
