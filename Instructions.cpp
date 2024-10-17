//
// Created by power on 10/6/2024.
//

#include "VoleMachine.h"
#include "Instructions.h"


void Instructions::load1(VoleMachine* machine) {
    short regIndex, memIndex;
    string reg, mem;

    reg = machine->ir[1];
    mem = machine->ir.substr(2);

    regIndex = Tools::hexToDec(reg), memIndex = Tools::hexToDec(mem);
    
    string memValue = machine->memoryManager.readMemory(memIndex);
    machine->registers[regIndex].setValue(memValue);
}

void Instructions::load2(VoleMachine* machine) {
    string reg, bit_pattern;
    short regIndex;

    bit_pattern = machine->ir.substr(2);

    reg = machine->ir[1];
    regIndex = Tools::hexToDec(reg);

    machine->registers[regIndex].setValue(bit_pattern);
}

void Instructions::store1(VoleMachine* machine) {
    short regIndex, memIndex;
    string reg, mem, bit_pattern;

    reg = machine->ir[1];
    mem = machine->ir.substr(2);

    regIndex = Tools::hexToDec(reg), memIndex = Tools::hexToDec(mem);

    bit_pattern = machine->registers[regIndex].getValue();

    machine->memoryManager.writeMemory(memIndex, bit_pattern);
}

void Instructions::move(VoleMachine *machine) {
    string reg1, reg2, carry;
    short reg1_idx, reg2_idx;

    reg1 = machine->ir[2], reg2 = machine->ir[3];
    reg1_idx = Tools::hexToDec(reg1), reg2_idx = Tools::hexToDec(reg2);

    carry = machine->registers[reg1_idx].getValue();
    machine->registers[reg2_idx].setValue(carry);
}

//todo store 3.1 R00

void Instructions::jump(VoleMachine* machine) {
    string reg0, reg1, pattern;
    short reg1_idx, reg2_idx, pattern_idx;
    reg1 = machine->ir[1];
    pattern = machine->ir.substr(2);
    reg1_idx = Tools::hexToDec(reg1);
    pattern_idx = Tools::hexToDec(pattern);
    if (machine->registers[0].getValue() == machine->registers[reg1_idx].getValue()) {
        machine->pc = pattern_idx;
    }

}

void Instructions::store2(VoleMachine* machine) {
    string reg;
    short reg_idx;
    reg = machine->ir[1];
    reg_idx = Tools::hexToDec(reg);
    machine->memoryManager.writeMemory(0, reg);
    cout << reg << endl;
}

