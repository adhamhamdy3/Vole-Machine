#ifndef VOLE_MACHINE_CU_H
#define VOLE_MACHINE_CU_H

#include "Memory.h"

class CPU;

class CU {
public:
    string value;
    CU() : value("NULL") {}
    void load1(CPU*, Memory*);
    void load2(CPU*);
    void store1(CPU*, Memory*);
    void store2(CPU*);
    void move(CPU*);
    void add1(CPU*);
    void add2(CPU*);
    void jump(CPU*);
};


#endif //VOLE_MACHINE_CU_H
