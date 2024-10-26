#include "Memory.h"

Memory::Memory() {
    fill(memory, memory + 256, "00");
}

void Memory::setCell(const int &address, const string &value) {
    try{
        if (address < 0 || address > 255)
            throw out_of_range("Out of range! address must be between [0-255].");

        //throw exception if the value is not valid
        memory[address] = value;
    } catch (const exception& e){
        cerr << "Error: " << e.what() << endl;
    }
}

string Memory::getCell(const int &address) const {
    string value{"N/A"};
    try {
        if (address < 0 || address > 255)
            throw out_of_range("Out of range! address must be between [0-255].");
        value = memory[address];
    }
    catch (const exception& e) {
        cerr << "Error:" << e.what() << endl;
    }
    return value;
}
