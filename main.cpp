#include <iostream>
#include "MainUI.h"
#include "Machine.h"

using namespace std;

void handleSubMenu(Machine& m, CPU* p, Memory* mem, MainUI& main);

int main() {
    Machine m;
    auto mem = m.memory;
    auto p = m.processor;
    MainUI main;
    bool run = true;

    while (run) {
        main.DisplayMenu();
        short int choice = main.inputChoice();

        if (choice == -1) continue;

        switch (choice) {
        case LOAD_FILE: {
            string fileName = main.inputFileName();
            m.loadProgramFile(fileName);
            handleSubMenu(m, p, mem, main);
            break;
        }
        case DISPLAY_MEMORY_STATUS:
            m.displayStatus();
            break;
        case DISPLAY_REGISTERS_STATUS:
            p->displayRegisters();
            break;
        case INPUT_INSTRUCTION: {
            string instruction = main.inputInstruction();
            m.inputInstruction(instruction);
            handleSubMenu(m, p, mem, main);
            break;
        }
        case EXIT_PROGRAM:
            cout << "Exiting...\n";
            run = false;
            break;
        default:
            cout << "Invalid Input! Please try again.\n";
        }
    }

    return 0;
}


void handleSubMenu(Machine& m, CPU* p, Memory* mem, MainUI& main) {
    bool subMenuRun = true;

    while (subMenuRun) {
        cout << "\n---- Sub Menu ----\n";
        cout << "1- Fetch.\n";
        cout << "2- Decode.\n";
        cout << "3- Execute.\n";
        cout << "4- Clear memory.\n";
        cout << "5- Clear registers.\n";
        cout << "6- Run one cycle.\n";
        cout << "7- Display Registers Status.\n";
        cout << "8- Display Memory Status.\n";
        cout << "9- Input Instruction into console.\n";
        cout << "10- Exit.\n";

        short int subChoice = main.inputChoice();
        if (subChoice == -1) continue;

        switch (subChoice) {
        case FETCH:
            p->fetchInstruction(mem);
            break;
        case DECODE:
            p->decodeInstruction();
            break;
        case EXECUTE:
            if (!p->executeInstruction(mem)) subMenuRun = false;
            break;
        case CLEAR_MEMORY:
            m.clearMemory();
            break;
        case CLEAR_REGISTERS:
            p->clearRegister();
            break;
        case RUN_CYCLE:
            m.processor->runOneCycle(mem);
            if(!m.running)subMenuRun = false;
            break;
        case DISPLAY_REGISTERS:
            p->displayRegisters();
            break;
        case DISPLAY_MEMORY:
            m.displayStatus();
            break;
        case INPUT_INSTRUCTION_CONSOLE: {
            string instruction = main.inputInstruction();
            m.inputInstruction(instruction);
            break;
        }
        case EXIT_SUBMENU:
            cout << "Exiting sub-menu...\n";
            subMenuRun = false;
            break;
        default:
            cout << "Invalid Input! Please try again.\n";
        }
    }
}



