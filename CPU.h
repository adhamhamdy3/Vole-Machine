#ifndef VOLE_MACHINE_CPU_H
#define VOLE_MACHINE_CPU_H

#include "Register.h"
#include "ALU.h"
#include "CU.h"
#include "Memory.h"

class CU;

class CPU {
private:
    int pc;
    string ir;
    Register* registers;
    ALU* alu;
    CU* cu;

public:
    explicit CPU(ALU* = nullptr, CU* = nullptr, Register* = nullptr);
    ~CPU();

    void fetchInstruction(Memory*);
    void decodeInstruction() const;
    bool executeInstruction(Memory*);
    void displayRegisters() const;
    void clearRegister() const;
    void runOneCycle(Memory*);
    friend class CU;
};


#endif //VOLE_MACHINE_CPU_H
