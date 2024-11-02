#include "Machine.h"

bool Machine::running = true;
short Machine::memoryIndex = 0;

Machine::Machine() {
    processor = new CPU(new ALU, new CU, new Register);
    memory = new Memory;
}

Machine::~Machine() {
    delete processor;
    delete memory;
}

void Machine::loadProgramFile(const string &filename) {
    ifstream inputFile(filename, ios::in);
    if (!inputFile) {
        cerr << "File could not open!" << endl;
        exit(EXIT_FAILURE);
    }

    string command;
    short memoryIndex = 0;

    while (inputFile >> command && memoryIndex < 256) {
        ALU::upperInstruction(command);
        if (ALU::isValid(command)) {
            string cell1 = command.substr(0, 2);
            string cell2 = command.substr(2);

            memory->setCell(memoryIndex++, cell1);

            if (memoryIndex < 256) {
                memory->setCell(memoryIndex++, cell2);
            }
            else {
                memoryIndex = 0;
            }

        }
        else {
            cerr << "Invalid command format: " << command << endl;
        }
    }
}

void Machine::clearMemory() {
    for (int i = 0; i < 256; ++i) {
        memory->setCell(i, "00");
    }
    memoryIndex = 0;
}

void Machine::displayStatus() const {
    for (int i = 0; i < 256; ++i) {
        cout << memory->getCell(i) << ' ';
        if (!((i+1) % 16)){
            cout << endl;
        }
    }
}
void Machine::inputInstruction(const string& command) {
    string carry = command;

    ALU::upperInstruction(carry);
    if(ALU::isValid(carry)){
        string cell1 = carry.substr(0, 2);
        string cell2 = carry.substr(2);

        if(memoryIndex<256)
            memory->setCell(memoryIndex++, cell1);

        if (memoryIndex < 256)
            memory->setCell(memoryIndex++, cell2);

        else
            memoryIndex = 0;
    } else {
        cerr << "This instruction is not valid!" << endl;
    }


}
