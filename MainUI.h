#ifndef MAINUI_H
#define MAINUI_H

#include <iostream>
#include <string>
#include "Machine.h"

enum MainMenuOptions {
    LOAD_FILE = 1,
    DISPLAY_MEMORY_STATUS,
    DISPLAY_REGISTERS_STATUS,
    INPUT_INSTRUCTION,
    EXIT_PROGRAM
};

enum SubMenuOptions {
    FETCH = 1,
    DECODE,
    EXECUTE,
    CLEAR_MEMORY,
    CLEAR_REGISTERS,
    RUN_CYCLE,
    DISPLAY_REGISTERS,
    DISPLAY_MEMORY,
    INPUT_INSTRUCTION_CONSOLE,
    EXIT_SUBMENU
};

class MainUI {
private:
    Machine machine;
    bool enterFileOrInstructions;

public:
    bool getFileOrInstruction();
    void DisplayMenu();
    std::string inputFileName();
    std::string inputInstruction();
    short int inputChoice();
};

#endif // MAINUI_H
