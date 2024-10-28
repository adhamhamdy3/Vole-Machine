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
    Memory* memory;
    CPU* processor;
    void loadProgramFile(const string&);
    void clearMemory();
    void displayStatus() const;
    void inputInstruction(const string&);


    ~Machine();
    friend class MainWindow;
};


#endif //VOLE_MACHINE_MACHINE_H
