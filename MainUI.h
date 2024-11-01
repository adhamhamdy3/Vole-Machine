#ifndef MAINUI_H
#define MAINUI_H

#include <iostream>
#include <string>
#include "Machine.h"

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
