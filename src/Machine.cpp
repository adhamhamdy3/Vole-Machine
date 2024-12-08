#include "Machine.h"
#include "Utilities.h"
bool Machine::running = true;
short Machine::memoryIndex = 10;
bool Machine::memoryLimitReached = false;

Machine::Machine() {
    processor = new CPU(new ALU, new CU, new Register);
    memory = new Memory;
    memoryFileStartIndex = 10;
}

Machine::~Machine() {
    delete processor;
    delete memory;
}

void Machine::setStartingAddress(const string& start){
    int START = Utilities::Conversions::hexToDec(start);
    processor->pc = START;
    memoryFileStartIndex = START;
    memoryIndex = START;
}

void Machine::loadProgramFile(const string &filename) {
    ifstream inputFile(filename, ios::in);
    if (!inputFile) {
        cerr << "File could not open!" << endl;
        exit(EXIT_FAILURE);
    }

    string command;

    while (inputFile >> command && memoryIndex < 256) {
        Utilities::Conversions::toUpper(command);

        if (Utilities::Validations::isValid(command)) {
            string cell1 = command.substr(0, 2);
            string cell2 = command.substr(2);

            memory->setCell(memoryIndex++, cell1);

            if (memoryIndex < 256) {
                memory->setCell(memoryIndex++, cell2);
            }
            else {
                memoryIndex = 10;
            }

        }
        else {
            cerr << "Invalid command format: " << command << endl;
        }
    }
    memoryIndex = processor->pc = 10;
    running = true;
}

void Machine::clearMemory() {
    for (int i = 0; i < 256; ++i) {
        memory->setCell(i, "00");
    }
    running = true;

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

    Utilities::Conversions::toUpper(carry);
    if(Utilities::Validations::isValid(carry)){
        string cell1 = carry.substr(0, 2);
        string cell2 = carry.substr(2);

        if(memoryIndex < 256)
            memory->setCell(memoryIndex++, cell1);

        if (memoryIndex < 256)
            memory->setCell(memoryIndex++, cell2);

        else
            memoryIndex = processor->pc = 10;
    } else {
        cerr << "This instruction is not valid!" << endl;
    }
    memoryIndex = processor->pc = 10;
    running = true;

}
