//
// Created by Adham Hamdy on 10/4/2024.
//

#ifndef VOLE_MACHINE_MEMORY_H
#define VOLE_MACHINE_MEMORY_H
#include <string>
#include <algorithm>
using namespace std;

class Memory {
private:
    string memoryCells[256];
public:
    Memory();
    ~Memory();


    friend class MemoryManager;
};


#endif //VOLE_MACHINE_MEMORY_H
