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
    memory->memoryCells[address] = value;
}

int MemoryManager::getAddress(const string &value) const {
    for (int i = 0; i < 256; ++i) {
        if (memory->memoryCells[i] == value)
            return i;
    }
    //todo catch error, address of the given value is not found
    return 0;
}

MemoryManager::~MemoryManager() {

}

string MemoryManager::readMemory(const int &address) const {
    return memory->memoryCells[address];
}

void MemoryManager::displayMemory() const {
    for (int i = 0; i < 256; ++i) {
        cout << memory->memoryCells[i] << ' ';
        if (!((i+1) % 16)){
            cout << endl;
        }
    }
}

