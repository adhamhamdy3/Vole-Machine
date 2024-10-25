//
// Created by Adham Hamdy on 10/4/2024.
//

#include "VoleMachine.h"

VoleMachine::VoleMachine() : memoryManager{ &memory }, pc{ 0 }, ir{ "00" }, running{ true } {

}

void VoleMachine::fetchInstruction() {
    string byte1, byte2;

    byte1 = memoryManager.readMemory(pc++);
    pc = (pc >= 256 ? 0 : pc);
    byte2 = memoryManager.readMemory(pc++);
    pc = (pc >= 256 ? 0 : pc);
    ir = byte1 + byte2;
}

bool VoleMachine::executeInstruction() {
    char op_code = ir[0];
    switch (op_code) {
    case '1':
        CU::load1(this);
        break;
    case '2':
        CU::load2(this);
        break;
    case '3':
        CU::store1(this);
        break;
    case 'C':
        cout << "adham" << endl;
        running = false;
        break;
    default:
        //todo implement default
        cout << "default" << endl;
    }
    return running;
}

void VoleMachine::clearRegisters() {
    for (auto& r : registers) {
        r.setValue("00");
    }
}

void VoleMachine::displayRegisters() const {
    for (int i = 0; i < 16; ++i) {
        cout << registers[i].getValue() << endl;
    }
}

void VoleMachine::loadProgram(const string& filename) {
    ifstream inputFile(filename, ios::in);
    if (!inputFile) {
        cerr << "File could not open!" << endl;
        exit(EXIT_FAILURE);
    }

    string command;
    short memoryIndex = 0;

    while (inputFile >> command && memoryIndex < 256) {
        if (command.size() == 4) {
            string cell1 = command.substr(0, 2);
            string cell2 = command.substr(2);

            memoryManager.writeMemory(memoryIndex++, cell1);

            if (memoryIndex < 256) {
                memoryManager.writeMemory(memoryIndex++, cell2);
            }
            else {
                cerr << "Memory overflow!" << endl;
                break;
            }

        }
        else {
            cerr << "Invalid command format: " << command << endl;
        }
    }

}


