#ifndef VOLE_MACHINE_ALU_H
#define VOLE_MACHINE_ALU_H

#include "CPU.h"

using namespace std;
class CPU;

class ALU{
public:
    void addTwosComplement(CPU*);
    void addFloatingPt(CPU*);
    void bitwiseAND(CPU*);
    void bitwiseOR(CPU*);
    void bitwiseXOR(CPU*);
    void rotateRight(CPU*);
};

#endif //VOLE_MACHINE_ALU_H
