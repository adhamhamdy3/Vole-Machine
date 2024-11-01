#include "CPU.h"
#include "Machine.h"

CPU::CPU(ALU *aluPtr, CU *cuPtr, Register *regPtr) : alu{aluPtr}, cu{cuPtr}, registers{regPtr}, pc{0}, ir{"0000"} {

}

CPU::~CPU() {
    delete alu;
    delete cu;
    delete registers;
}

void CPU::fetchInstruction(Memory *mem) {
    string byte1, byte2;

    byte1 = mem->getCell(pc++);
    pc = (pc + 1 >= 256 ? 0 : pc);

    byte2 = mem->getCell(pc++);
    pc = (pc + 1 >= 256 ? 0 : pc);

    ir = byte1 + byte2;
}
//0x6e3f30 mem address,, 0x6e3c10 cpu address
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
                cu->store2(this);
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

void CPU::decodeInstruction() const {
    char op_code = ir[0];
    switch (op_code) {
        case '0':
            cout << "NOTHING. Advance to the next step." << endl;
            break;
        case '1':
            cout << "LOAD Register " << ir[1] << " with the content of memory at address " << ir.substr(2) << endl;
            break;
        case '2':
            cout << "LOAD Register " << ir[1] << " with bit pattern " << ir.substr(2) << endl;
            break;
        case '3':
            cout << "STORE the bit pattern of Register " << ir[1] << " in memory at address " << ir.substr(2) << endl;
            break;
        case '4':
            cout << "MOVE the bit pattern of Register " << ir[2] << " A into Register " << ir[3] << endl;
            break;
        case '5':
            cout << "ADD the bit patterns of Registers " << ir[2] <<  " and " << ir[3]
                << " as if they were integers, and store the result in Register " << ir[1] << endl;
            break;
        case '6':
            cout << "ADD the bit patterns of Registers " << ir[2] <<  " and " << ir[3]
                 << " if they were floating point numbers, and store the result in Register " << ir[1] << endl;
            break;
        case 'B':
            cout << "JUMP to the instruction located in memory at address " << ir.substr(2)
                << " if the bit pattern in Register  " << ir[1] << " matches with the bit pattern in Register 0." << endl;
            break;
        case 'C':
            cout << "HALT the execution." << endl;
            break;
    }
}


void CPU::runOneCycle(Memory* mem){
    CPU::fetchInstruction(mem);
    CPU::decodeInstruction();
    CPU::executeInstruction(mem);
}
