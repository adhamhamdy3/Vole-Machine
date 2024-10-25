//
// Created by Adham Hamdy on 10/4/2024.
//

#ifndef VOLE_MACHINE_VOLEMACHINE_H
#define VOLE_MACHINE_VOLEMACHINE_H
#include "Register.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "ALU.h"
#include "CU.h"
#include "fstream"

class VoleMachine {
private:
    short pc;
    string ir;
    Register registers[16];
    Memory memory;
    bool running;
public:
    VoleMachine();
    MemoryManager memoryManager;
    void fetchInstruction();
    bool executeInstruction();
    void displayRegisters() const;
    void clearRegisters();
    void loadProgram(const string&);

    friend class CU;
};


#endif //VOLE_MACHINE_VOLEMACHINE_H
