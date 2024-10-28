#ifndef VOLE_MACHINE_CPU_H
#define VOLE_MACHINE_CPU_H

#include "Register.h"
#include "ALU.h"
#include "CU.h"
#include "Memory.h"

class CU;
class MainWindow;

class CPU {
private:
    int pc;
    string ir;
    Register* registers;
    ALU* alu;
    CU* cu;
    string decodeMessage;

public:

    explicit CPU(ALU* = nullptr, CU* = nullptr, Register* = nullptr);
    ~CPU();

    void fetchInstruction(Memory*);
    void decodeInstruction();
    bool executeInstruction(Memory*);
    void displayRegisters() const;
    void clearRegister() const;
    friend class CU;
    friend class MainWindow;
};


#endif //VOLE_MACHINE_CPU_H
