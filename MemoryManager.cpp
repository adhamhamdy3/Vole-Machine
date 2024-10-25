//
// Created by Adham Hamdy on 10/5/2024.
//

#include "MemoryManager.h"

MemoryManager::MemoryManager(Memory *m) : memory{m}{

}

void MemoryManager::setMemory(Memory *m) {
    memory = m;
}

void MemoryManager::clear() {
    fill(memory->memoryCells, memory->memoryCells + 256, "00");
}

bool MemoryManager::isFound(const string &value) const {
    for (int i = 0; i < 256; ++i) {
        if (memory->memoryCells[i] == value)
            return true;
    }
     
    return false;
}

void MemoryManager::writeMemory(const int &address, const string &value) {
    try {
        if (address < 0 || address > 255)
            throw out_of_range("Address is out of range [0-255].");
        /*
         if value is not valid
         throw invalid_argument(""Value cannot be empty."")*/

        memory->memoryCells[address] = value;
    } catch (const exception& e){
        cerr << "Error: " << e.what() << endl;
    }
}

int MemoryManager::getAddress(const string &value) const {
    //todo catch error, address of the given value is not found or the value inserted is not found
    short i{-1};
    try {
        if (!isFound(value))
            throw invalid_argument("This value is not found in the memory");

        for (i = 0; i < 256; ++i) {
            if (memory->memoryCells[i] == value)
                break;
        }
        /*
        if value is not valid
        throw invalid_argument(""Value cannot be empty."")
        */
    } catch (const exception& e){
        cerr << "Error: " << e.what() << endl;
    }
    return i;
}

MemoryManager::~MemoryManager() {

}

string MemoryManager::readMemory(const int &address) const {
    string value;

    try {
        if (address < 0 || address > 255)
            throw out_of_range("Address is out of range [0-255].");

        value = memory->memoryCells[address];
    } catch (const exception& e){
        cerr << "Error: " << e.what() << endl;
    }

    return value;
}

void MemoryManager::displayMemory() const {
    for (int i = 0; i < 256; ++i) {
        cout << memory->memoryCells[i] << ' ';
        if (!((i+1) % 16)){
            cout << endl;
        }
    }
}

