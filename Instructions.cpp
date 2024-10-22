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
void Instructions::add1(VoleMachine* machine) {
    int reg_num1, reg_num2, res_num;
    short reg1_index, reg2_index, res_index;
    string reg1, reg2, res;

    reg1 = machine->ir[2];
    reg2 = machine->ir[3];
    res = machine->ir[1];
    reg1_index = Tools::hexToDec(reg1) ,reg2_index = Tools::hexToDec(reg2);
    res_index = Tools::hexToDec(res);

    reg_num1 = stoi(machine->registers[reg1_index].getValue(),0,16);
    reg_num2 = stoi(machine->registers[reg2_index].getValue(),0,16);
    res_num = reg_num1 + reg_num2;

    machine->registers[res_index].setValue(Tools::decToHex(res_num));
}


//add2

void Instructions::add2(VoleMachine* machine) {
    double reg_num1, reg_num2, res_num;
    short reg1_index, reg2_index, res_index;
    string reg1, reg2, res;

    reg1 = machine->ir[2];
    reg2 = machine->ir[3];
    res = machine->ir[1];
    reg1_index = Tools::hexToDec(reg1), reg2_index = Tools::hexToDec(reg2);
    res_index = Tools::hexToDec(res);

    reg_num1 = Tools::hexToDecFloat(machine->registers[reg1_index].getValue());
    reg_num2 = Tools::hexToDecFloat(machine->registers[reg2_index].getValue());
    res_num = reg_num1 + reg_num2;

    machine->registers[res_index].setValue(Tools::decToHexFloat(res_num));
}
