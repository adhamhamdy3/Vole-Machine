//
// Created by Adham Hamdy on 10/5/2024.
//

#ifndef VOLE_MACHINE_MEMORYMANAGER_H
#define VOLE_MACHINE_MEMORYMANAGER_H
#include "Memory.h"
#include <iostream>
#include <stdexcept>
class MemoryManager {
private:
    Memory* memory;
public:
    explicit MemoryManager(Memory* = nullptr);
    ~MemoryManager();
    void setMemory(Memory*);
    void clear();
    bool isFound(const string&) const;
    void writeMemory(const int&, const string&);
    string readMemory(const int&) const;
    int getAddress(const string&) const;
    void displayMemory() const;
};


#endif //VOLE_MACHINE_MEMORYMANAGER_H
