//
// Created by Adham Hamdy on 10/4/2024.
//

#ifndef VOLE_MACHINE_VOLEMACHINE_H
#define VOLE_MACHINE_VOLEMACHINE_H
#include "Register.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Tools.h"
#include "Instructions.h"
#include "fstream"

class VoleMachine {
private:
    Register registers[16];
    Memory memory;
    short pc;
    string ir;
    bool running;
public:
    VoleMachine();
    MemoryManager memoryManager;
    void loadProgram(const string&);
    void fetchInstruction();
    bool executeInstruction();
    void displayRegisters() const;
    void clearRegisters();
    friend class Instructions;
};


#endif //VOLE_MACHINE_VOLEMACHINE_H
