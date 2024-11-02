#include "CPU.h"
#include "Machine.h"


CPU::CPU(ALU *aluPtr, CU *cuPtr, Register *regPtr) : pc{0}, ir{"0000"}, registers{regPtr}, alu{aluPtr}, cu{cuPtr} {
    decodeMessage = "NOTHING. Advance to the next step.";
}

CPU::~CPU() {
    delete alu;
    delete cu;
    delete registers;
}

void CPU::fetchInstruction(Memory *mem) {
    string byte1, byte2;

    byte1 = mem->getCell(pc++);
    if(pc + 1 >= 256) return void (pc = 0);


    byte2 = mem->getCell(pc++);
    if(pc + 1 >= 256) return void (pc = 0);

    ir = byte1 + byte2;
}

void CPU::displayRegisters() const {
    for (int i = 0; i < 16; ++i) {
        cout << registers->getCell(i) << ' ';
    }
    cout << endl;
}

void CPU::clearRegister() const {
    for (int i = 0; i < 16; ++i) {
        registers->setCell(i, "00");
    }
}

bool CPU::executeInstruction(Memory* mem) {
    char op_code = ir[0];
    switch (op_code) {
        case '1':
            cu->load1(this, mem);
            break;
        case '2':
            cu->load2(this);
            break;
        case '3':
            if (ir.substr(2) != "00")
                cu->store1(this, mem);
            else
                cu->store2(this, mem);
            break;
        case '4':
            cu->move(this);
            break;
        case '5':
            cu->add1(this);
            break;
        case '6':
            cu->add2(this);
            break;
        case 'B':
            cu->jump(this);
            break;
        case 'C':
            cout << "Exit..." << endl;
            Machine::running = false;

    }
    return Machine::running;
}

void CPU::decodeInstruction() {
    char op_code = ir[0];
    switch (op_code) {
    case '0':
        decodeMessage = "NOTHING. Advance to the next step.";
        break;
    case '1':
        decodeMessage = "LOAD Register " + string(1, ir[1]) +
                        " with the content of memory at address " + ir.substr(2) + ".";
        break;
    case '2':
        decodeMessage = "LOAD Register " + string(1, ir[1]) +
                        " with bit pattern " + ir.substr(2) + ".";
        break;
    case '3':
        decodeMessage = "STORE the bit pattern of Register " + string(1, ir[1]) +
                        " in memory at address " + ir.substr(2) + ".";
        break;
    case '4':
        decodeMessage = "MOVE the bit pattern of Register " + string(1, ir[2]) +
                        " into Register " + string(1, ir[3]) + ".";
        break;
    case '5':
        decodeMessage = "ADD the bit patterns of Registers " + string(1, ir[2]) +
                        " and " + string(1, ir[3]) + " as if they were integers, and store the result in Register " +
                        string(1, ir[1]) + ".";
        break;
    case '6':
        decodeMessage = "ADD the bit patterns of Registers " + string(1, ir[2]) +
                        " and " + string(1, ir[3]) + " if they were floating point numbers, and store the result in Register " +
                        string(1, ir[1]) + ".";
        break;
    case 'B':
        decodeMessage = "JUMP to the instruction located in memory at address " + ir.substr(2) +
                        " if the bit pattern in Register " + string(1, ir[1]) +
                        " matches with the bit pattern in Register 0.";
        break;
    case 'C':
        decodeMessage = "HALT the execution.";
        break;
    default:
        decodeMessage = "Unknown operation code.";
        break;
    }
}

void CPU::runOneCycle(Memory* mem){
    CPU::fetchInstruction(mem);
    CPU::decodeInstruction();
    CPU::executeInstruction(mem);
}
