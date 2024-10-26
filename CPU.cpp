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
