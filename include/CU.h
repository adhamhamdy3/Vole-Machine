#ifndef VOLE_MACHINE_CU_H
#define VOLE_MACHINE_CU_H

#include "Memory.h"

class CPU;

class CU {
private:
    short getRegisterIndex(const char&);
    short getMemoryIndex(const string &);
public:
    string ASCIIstr;
    string HEXstr;
    CU() : ASCIIstr(""), HEXstr("") {}
    void load_memXYtoR(CPU*, Memory*);
    void load_XYtoR(CPU*);
    void store_R_to_memXY(CPU*, Memory*);
    void storeAndScreen(CPU*, Memory*);
    void jumpIfGreater(CPU*);
    void move_R_to_S(CPU*);
    void jumpEQ(CPU*);
};


#endif //VOLE_MACHINE_CU_H
