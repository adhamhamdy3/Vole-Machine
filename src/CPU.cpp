#include "CPU.h"
#include "Machine.h"


CPU::CPU(ALU* aluPtr, CU* cuPtr, Register* regPtr) : pc{ 10 }, ir{ "0000" }, registers{ regPtr }, alu{ aluPtr }, cu{ cuPtr } {
    decodeMessage = "NOTHING. Advance to the next step.";
}

CPU::~CPU() {
    delete alu;
    delete cu;
    delete registers;
}

void CPU::fetchInstruction(Memory* mem) {
    string byte1, byte2;

    if (pc + 1 >= 256) {
        pc = 10;
        Machine::memoryLimitReached = true;
        return;
    }
    byte1 = mem->getCell(pc++);

    if (pc + 1 >= 256) {
        pc = 10;
        Machine::memoryLimitReached = true;
        return;
    }
    byte2 = mem->getCell(pc++);

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
        // Memory Operations
        case '1': // Load memory address XY to register
            cu->load_memXYtoR(this, mem);
            break;
        case '2': // Load value XY to register
            cu->load_XYtoR(this);
            break;
        case '3': // Store register to memory or memory and screen
            if (ir.substr(2) != "00")
                cu->store_R_to_memXY(this, mem);
            else
                cu->storeAndScreen(this, mem);
            break;

            // Register and Data Manipulation
        case '4': // Move register R to S
            cu->move_R_to_S(this);
            break;

            // Arithmetic Operations
        case '5': // Add two's complement
            alu->addTwosComplement(this);
            break;
        case '6': // Add floating-point numbers
            alu->addFloatingPt(this);
            break;

            // Bitwise Operations
        case '7': // Bitwise OR
            alu->bitwiseOR(this);
            break;
        case '8': // Bitwise AND
            alu->bitwiseAND(this);
            break;
        case '9': // Bitwise XOR
            alu->bitwiseXOR(this);
            break;
        case 'A': // Rotate right
            alu->rotateRight(this);
            break;

            // Control Flow
        case 'B': // Jump if equal
            cu->jumpEQ(this);
            break;

            // System Control
        case 'C': // Exit machine
            Machine::running = false;
            break;

        case 'D':
            cu->jumpIfGreater(this);
            break;
    }
    return Machine::running;
}


void CPU::decodeInstruction() {
    char op_code = ir[0];
    switch (op_code) {
        // No Operation
        case '0':
            decodeMessage = "NOTHING. Advance to the next step.";
            break;

            // Load Instructions
        case '1':
            decodeMessage = "LOAD Register " + string(1, ir[1]) +
                            " with the content of memory at address " + ir.substr(2) + ".";
            break;
        case '2':
            decodeMessage = "LOAD Register " + string(1, ir[1]) +
                            " with bit pattern " + ir.substr(2) + ".";
            break;

            // Store Instruction
        case '3':
            decodeMessage = "STORE the bit pattern of Register " + string(1, ir[1]) +
                            " in memory at address " + ir.substr(2) + ".";
            break;

            // Move Instruction
        case '4':
            decodeMessage = "MOVE the bit pattern of Register " + string(1, ir[2]) +
                            " into Register " + string(1, ir[3]) + ".";
            break;

            // Arithmetic Instructions
        case '5':
            decodeMessage = "ADD the bit patterns of Registers " + string(1, ir[2]) +
                            " and " + string(1, ir[3]) + " as if they were integers, and store the result in Register " +
                            string(1, ir[1]) + ".";
            break;
        case '6':
            decodeMessage = "ADD the bit patterns of Registers " + string(1, ir[2]) +
                            " and " + string(1, ir[3]) + " as if they were floating-point numbers, and store the result in Register " +
                            string(1, ir[1]) + ".";
            break;

            // Bitwise Logic Instructions
        case '7':
            decodeMessage = "OR the bit patterns of Registers " + string(1, ir[2]) +
                            " and " + string(1, ir[3]) + ", and store the result in Register " +
                            string(1, ir[1]) + ".";
            break;
        case '8':
            decodeMessage = "AND the bit patterns of Registers " + string(1, ir[2]) +
                            " and " + string(1, ir[3]) + ", and store the result in Register " +
                            string(1, ir[1]) + ".";
            break;
        case '9':
            decodeMessage = "XOR the bit patterns of Registers " + string(1, ir[2]) +
                            " and " + string(1, ir[3]) + ", and store the result in Register " +
                            string(1, ir[1]) + ".";
            break;

            // Rotate Instruction
        case 'A':
            decodeMessage = "ROTATE the bit pattern in Register " + string(1, ir[1]) +
                            " one bit to the right " + string(1, ir[3]) + " times.";
            break;

            // Jump Instruction
        case 'B':
            decodeMessage = "JUMP to the instruction located in memory at address " + ir.substr(2) +
                            " if the bit pattern in Register " + string(1, ir[1]) +
                            " matches with the bit pattern in Register 0.";
            break;

            // Halt Instruction
        case 'C':
            decodeMessage = "HALT the execution.";
            break;
        case 'D':
            decodeMessage = "Jump to instruction in memory cell " +
                            ir.substr(2) + " if the content of register " +
                            string(1, ir[1]) + " is greater than (>) that of register 0.";
            break;
    }

    // Output the decoded information
    cout << "PC: " << pc << endl;
    cout << "IR: " << ir << endl;
    cout << decodeMessage << endl;
}


void CPU::runOneCycle(Memory* mem) {
    CPU::fetchInstruction(mem);
    CPU::decodeInstruction();
    CPU::executeInstruction(mem);
}
