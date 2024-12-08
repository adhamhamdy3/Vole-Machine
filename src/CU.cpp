#include "CU.h"
#include "CPU.h"
#include "Utilities.h"

short CU::getRegisterIndex(const char& regChar) {
    return Utilities::Conversions::hexToDec(string(1, regChar));
}

short CU::getMemoryIndex(const string &mem) {
    return Utilities::Conversions::hexToDec(mem);
}

void CU::load_memXYtoR(CPU *cpuPtr, Memory *memPtr) {
    short regIndex = getRegisterIndex(cpuPtr->ir[1]);
    short memIndex = getMemoryIndex(cpuPtr->ir.substr(2));
    cpuPtr->registers->setCell(regIndex, memPtr->getCell(memIndex));
}

void CU::load_XYtoR(CPU *cpuPtr) {
    short regIndex = getRegisterIndex(cpuPtr->ir[1]);
    string bit_pattern = cpuPtr->ir.substr(2);
    cpuPtr->registers->setCell(regIndex, bit_pattern);
}

void CU::store_R_to_memXY(CPU *cpuPtr, Memory *memPtr) {
    short regIndex = getRegisterIndex(cpuPtr->ir[1]);
    short memIndex = getMemoryIndex(cpuPtr->ir.substr(2));
    memPtr->setCell(memIndex, cpuPtr->registers->getCell(regIndex));
}

void CU::storeAndScreen(CPU *cpuPtr, Memory* memPtr) {
    store_R_to_memXY(cpuPtr, memPtr);
    ASCIIstr += Utilities::Conversions::strToASCII(memPtr->getCell(0));
    HEXstr += memPtr->getCell(0);
    cout << memPtr->getCell(0) << endl;
}

void CU::move_R_to_S(CPU *cpuPtr) {
    short reg1_idx = getRegisterIndex(cpuPtr->ir[2]);
    short reg2_idx = getRegisterIndex(cpuPtr->ir[3]);
    cpuPtr->registers->setCell(reg2_idx, cpuPtr->registers->getCell(reg1_idx));
}

void CU::jumpEQ(CPU *cpuPtr) {
    short reg1_idx = getRegisterIndex(cpuPtr->ir[1]);
    short pattern_idx = getMemoryIndex(cpuPtr->ir.substr(2));

    if (cpuPtr->registers->getCell(0) == cpuPtr->registers->getCell(reg1_idx)) {
        cpuPtr->pc = pattern_idx;
    }
}

void CU::jumpIfGreater(CPU *cpuPtr){
    int R = Utilities::Conversions::hexToDec(string(1, cpuPtr->ir[1]));
    int regValue = Utilities::Conversions::hexToDec(cpuPtr->registers->getCell(R));
    int zeroValue = Utilities::Conversions::hexToDec(cpuPtr->registers->getCell(0));

    if(regValue > zeroValue){
        cpuPtr->pc = Utilities::Conversions::hexToDec(cpuPtr->ir.substr(2));
    }
}
