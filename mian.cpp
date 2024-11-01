#include <iostream>
#include "MainUI.h"

using namespace std;

int main() {
    Machine m;
    auto mem = m.memory;
    auto p = m.processor;
    MainUI main;
    bool run = true;

    while (run) {
        main.DisplayMenu();
        short int choice = main.inputChoice();
        if (choice == -1) {
            continue;
        }

        switch (choice) {
        case 1: {
            string fileName = main.inputFileName();
            m.loadProgramFile(fileName);
            while (run) {
                cout << "1-fetch \n";
                cout << "2-decode\n";
                cout << "3-execute\n";
                cout << "4-clear memory\n";
                cout << "5-clear registers\n";
                cout << "6-run one cycle\n";
                cout << "7-Display Registers Status\n";
                cout << "8-Display Memory Status\n";
                cout << "9. Input Instruction into console\n";
                cout << "10-Exit\n";
                short int input = main.inputChoice();
                switch (input) {
                case 1: {
                    p->fetchInstruction(mem);
                    break;
                }
                case 2: {
                    p->decodeInstruction();
                    break;
                }
                case 3: {
                    if (!p->executeInstruction(mem)) {
                        run = false;
                    }
                    break;
                }
                case 4: {
                    m.clearMemory();
                    break;
                }
                case 5: {
                    p->clearRegister();
                    break;
                }
                case 6: {
                    p->fetchInstruction(mem);
                    p->decodeInstruction();
                    if (!p->executeInstruction(mem)) {
                        run = false;
                    }
                    break;
                }
                case 7: {
                    p->displayRegisters();
                    break;
                }
                case 8: {
                    m.displayStatus();
                    break;
                }
                case 9: {
                    string instruction = main.inputInstruction();
                    m.inputInstruction(instruction);
                    break;
                }
                case 10: {
                    cout << "Exiting\n";
                    run = false;
                    break;
                }
                }
            }
            break;
        }
        case 2: {
            m.displayStatus();
            break;
        }
        case 3: {
            p->displayRegisters();
            break;
        }
        case 4: {
            string instruction = main.inputInstruction();
            m.inputInstruction(instruction);
            while (run) {
                cout << "1-fetch \n";
                cout << "2-decode\n";
                cout << "3-execute\n";
                cout << "4-clear memory\n";
                cout << "5-clear registers\n";
                cout << "6-run one cycle\n";
                cout << "7-Display Registers Status\n";
                cout << "8-Display Memory Status\n";
                cout << "9. Input Instruction into console\n";
                cout << "10-Exit\n";
                short int input = main.inputChoice();
                switch (input) {
                case 1: {
                    p->fetchInstruction(mem);
                    break;
                }
                case 2: {
                    p->decodeInstruction();
                    break;
                }
                case 3: {
                    if (!p->executeInstruction(mem)) {
                        run = false;
                    }
                    break;
                }
                case 4: {
                    m.clearMemory();
                    break;
                }
                case 5: {
                    p->clearRegister();
                    break;
                }
                case 6: {
                    p->fetchInstruction(mem);
                    p->decodeInstruction();
                    if (!p->executeInstruction(mem)) {
                        run = false;
                    }
                    break;
                }
                case 7: {
                    p->displayRegisters();
                    break;
                }
                case 8: {
                    m.displayStatus();
                    break;
                }
                case 9: {
                    string instruction = main.inputInstruction();
                    m.inputInstruction(instruction);
                    break;
                }

                case 10: {
                    cout << "Exiting\n";
                    run = false;
                    break;
                }
                }
            }
            break;
        }
        case 5: {
            cout << "Exiting\n";
            run = false;
            break;
        }
        default:
            cout << "Invalid Input Please try again\n";
        }
    }
    return 0;
}
