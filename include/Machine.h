#ifndef VOLE_MACHINE_MACHINE_H
#define VOLE_MACHINE_MACHINE_H

#include "Memory.h"
#include "CPU.h"
#include <fstream>

class MainWindow;

class Machine {
public:
    Machine();

    static short memoryIndex;
    static bool running;
    static bool memoryLimitReached;

    Memory* memory;
    CPU* processor;

    void loadProgramFile(const string&);
    void clearMemory();
    void displayStatus() const;
    void inputInstruction(const string&);
    void setStartingAddress(const string&);
    short memoryFileStartIndex;

    ~Machine();
    friend class MainWindow;
};


#endif //VOLE_MACHINE_MACHINE_H
