#include "CU.h"
#include "CPU.h"

void CU::load1(CPU *cpuPtr, Memory *memPtr) {
    short regIndex, memIndex;
    string reg, mem;

    reg = cpuPtr->ir[1];
    mem = cpuPtr->ir.substr(2);

    regIndex = cpuPtr->alu->hexToDec(reg), memIndex = cpuPtr->alu->hexToDec(mem);

    string memValue = memPtr->getCell(memIndex);
    cpuPtr->registers->setCell(regIndex, memValue);
}

void CU::load2(CPU *cpuPtr) {
    string reg, bit_pattern;
    short regIndex;

    bit_pattern = cpuPtr->ir.substr(2);

    reg = cpuPtr->ir[1];
    regIndex = cpuPtr->alu->hexToDec(reg);

    cpuPtr->registers->setCell(regIndex, bit_pattern);
}

void CU::store1(CPU *cpuPtr, Memory *memPtr) {
    short regIndex, memIndex;
    string reg, mem, bit_pattern;

    reg = cpuPtr->ir[1];
    mem = cpuPtr->ir.substr(2);

    regIndex = cpuPtr->alu->hexToDec(reg), memIndex = cpuPtr->alu->hexToDec(mem);

    bit_pattern = cpuPtr->registers->getCell(regIndex);

    memPtr->setCell(memIndex, bit_pattern);
}

void CU::store2(CPU* cpuPtr, Memory* memPtr) {
    string reg;
    short reg_idx;
    reg = cpuPtr->ir[1];
    reg_idx = cpuPtr->alu->hexToDec(reg);
    string value = cpuPtr->registers->getCell(reg_idx);
    memPtr->setCell(0, value);
    cout << value << endl;
}

void CU::move(CPU *cpuPtr) {
    string reg1, reg2, carry;
    short reg1_idx, reg2_idx;

    reg1 = cpuPtr->ir[2], reg2 = cpuPtr->ir[3];
    reg1_idx = cpuPtr->alu->hexToDec(reg1), reg2_idx = cpuPtr->alu->hexToDec(reg2);

    carry = cpuPtr->registers->getCell(reg1_idx);
    cpuPtr->registers->setCell(reg2_idx, carry);
}

void CU::add1(CPU *cpuPtr) {
    int reg_num1, reg_num2, res_num;
    short reg1_index, reg2_index, res_index;
    string reg1, reg2, res;

    reg1 = cpuPtr->ir[2];
    reg2 = cpuPtr->ir[3];
    res = cpuPtr->ir[1];
    reg1_index = cpuPtr->alu->hexToDec(reg1) , reg2_index = cpuPtr->alu->hexToDec(reg2);
    res_index = cpuPtr->alu->hexToDec(res);

    reg_num1 = stoi(cpuPtr->registers->getCell(reg1_index), 0, 16);
    reg_num2 = stoi(cpuPtr->registers->getCell(reg2_index), 0, 16);

    res_num = reg_num1 + reg_num2;
    cpuPtr->registers->setCell(res_index, cpuPtr->alu->decToHex(res_num));
}

void CU::add2(CPU *cpuPtr) {
    double reg_num1, reg_num2, res_num;
    short reg1_index, reg2_index, res_index;
    string reg1, reg2, res;

    reg1 = cpuPtr->ir[2];
    reg2 = cpuPtr->ir[3];
    res = cpuPtr->ir[1];
    reg1_index = cpuPtr->alu->hexToDec(reg1), reg2_index = cpuPtr->alu->hexToDec(reg2);
    res_index = cpuPtr->alu->hexToDec(res);

    reg_num1 = cpuPtr->alu->hexToDecFloat(cpuPtr->registers->getCell(reg1_index));
    reg_num2 = cpuPtr->alu->hexToDecFloat(cpuPtr->registers->getCell(reg2_index));

    res_num = reg_num1 + reg_num2;

    cpuPtr->registers->setCell(res_index, cpuPtr->alu->decToHexFloat(res_num));
}

void CU::jump(CPU *cpuPtr) {
    string reg0, reg1, pattern;
    short reg1_idx, pattern_idx;

    reg1 = cpuPtr->ir[1];
    pattern = cpuPtr->ir.substr(2);
    reg1_idx = cpuPtr->alu->hexToDec(reg1);

    pattern_idx = cpuPtr->alu->hexToDec(pattern);

    if (cpuPtr->registers->getCell(0) == cpuPtr->registers->getCell(reg1_idx)) {
        cpuPtr->pc = pattern_idx;
    }
}

