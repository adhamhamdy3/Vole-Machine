#ifndef VOLE_MACHINE_MACHINE_H
#define VOLE_MACHINE_MACHINE_H

#include "Memory.h"
#include "CPU.h"
#include <fstream>

class Machine {
public:
    Machine();
    static bool running;
    Memory* memory;
    CPU* processor;
    void loadProgramFile(const string&);
    void clearMemory();
    void displayStatus() const;
    void inputInstruction(const string&);

    ~Machine();
};


#endif //VOLE_MACHINE_MACHINE_H
