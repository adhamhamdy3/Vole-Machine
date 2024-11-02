#include "CU.h"
#include "CPU.h"

short CU::getRegisterIndex(CPU *cpuPtr, char regChar) {
    return cpuPtr->alu->hexToDec(string(1, regChar));
}

short CU::getMemoryIndex(CPU *cpuPtr, const string &mem) {
    return cpuPtr->alu->hexToDec(mem);
}

void CU::load1(CPU *cpuPtr, Memory *memPtr) {
    short regIndex = getRegisterIndex(cpuPtr, cpuPtr->ir[1]);
    short memIndex = getMemoryIndex(cpuPtr, cpuPtr->ir.substr(2));
    cpuPtr->registers->setCell(regIndex, memPtr->getCell(memIndex));
}

void CU::load2(CPU *cpuPtr) {
    short regIndex = getRegisterIndex(cpuPtr, cpuPtr->ir[1]);
    string bit_pattern = cpuPtr->ir.substr(2);
    cpuPtr->registers->setCell(regIndex, bit_pattern);
}

void CU::store1(CPU *cpuPtr, Memory *memPtr) {
    short regIndex = getRegisterIndex(cpuPtr, cpuPtr->ir[1]);
    short memIndex = getMemoryIndex(cpuPtr, cpuPtr->ir.substr(2));
    memPtr->setCell(memIndex, cpuPtr->registers->getCell(regIndex));
}

void CU::store2(CPU *cpuPtr, Memory* memPtr) {
    store1(cpuPtr, memPtr);
    cout << memPtr->getCell(0) << endl;
}

void CU::move(CPU *cpuPtr) {
    short reg1_idx = getRegisterIndex(cpuPtr, cpuPtr->ir[2]);
    short reg2_idx = getRegisterIndex(cpuPtr, cpuPtr->ir[3]);
    cpuPtr->registers->setCell(reg2_idx, cpuPtr->registers->getCell(reg1_idx));
}

void CU::add1(CPU* cpuPtr) {
    int reg_num1, reg_num2, res_num;
    short reg1_index, reg2_index, res_index;
    string reg1, reg2, res;

    reg1 = cpuPtr->ir[2];
    reg2 = cpuPtr->ir[3];
    res = cpuPtr->ir[1];
    reg1_index = cpuPtr->alu->hexToDec(reg1), reg2_index = cpuPtr->alu->hexToDec(reg2);
    res_index = cpuPtr->alu->hexToDec(res);

    reg_num1 = cpuPtr->alu->hexToTwosComplement(cpuPtr->registers->getCell(reg1_index));
    reg_num2 = cpuPtr->alu->hexToTwosComplement(cpuPtr->registers->getCell(reg2_index));

    res_num = reg_num1 + reg_num2;
    cpuPtr->registers->setCell(res_index, cpuPtr->alu->decimalToHexTwosComplement(res_num));
}

void CU::add2(CPU* cpuPtr) {
    float reg_num1, reg_num2, res_num;
    short reg1_index, reg2_index, res_index;
    string reg1, reg2, res;

    reg1 = cpuPtr->ir[2];
    reg2 = cpuPtr->ir[3];
    res = cpuPtr->ir[1];
    reg1_index = cpuPtr->alu->hexToDec(reg1), reg2_index = cpuPtr->alu->hexToDec(reg2);
    res_index = cpuPtr->alu->hexToDec(res);

    reg_num1 = cpuPtr->alu->hexToFloat(cpuPtr->registers->getCell(reg1_index));
    reg_num2 = cpuPtr->alu->hexToFloat(cpuPtr->registers->getCell(reg2_index));


    res_num = reg_num1 + reg_num2;

    cpuPtr->registers->setCell(res_index, cpuPtr->alu->floatToHex(res_num));
}

void CU::jump(CPU *cpuPtr) {
    short reg1_idx = getRegisterIndex(cpuPtr, cpuPtr->ir[1]);
    short pattern_idx = getMemoryIndex(cpuPtr, cpuPtr->ir.substr(2));

    if (cpuPtr->registers->getCell(0) == cpuPtr->registers->getCell(reg1_idx)) {
        cpuPtr->pc = pattern_idx;
    }
}
