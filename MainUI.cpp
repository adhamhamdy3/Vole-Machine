#include "MainUI.h"
#include <limits>
using namespace std;

bool MainUI::getFileOrInstruction() {
    char choice;
    cout << "Enter input method (f for file, i for instructions): ";
    cin >> choice;
    enterFileOrInstructions = (choice == 'f' || choice == 'F');
    return enterFileOrInstructions;
}

void MainUI::DisplayMenu() {
    cout << "---- Vole Machine Menu ----\n";
    cout << "1. Load File\n";
    cout << "2. Display Memory Status\n";
    cout << "3. Display Registers Status\n";
    cout << "4. Input Instruction into console\n";
    cout << "5. Exit\n";
}

string MainUI::inputFileName() {
    string fileName;
    cout << "Enter the file name to load: ";
    cin >> fileName;
    return fileName;
}

string MainUI::inputInstruction() {
    string instruction;
    cout << "Enter an instruction: ";
    cin.ignore();
    getline(cin, instruction);
    return instruction;
}

short int MainUI::inputChoice() {
    short int choice;
    cout << "Choose an option: ";
    cin >> choice;
    if (cin.fail() || choice < 1 || choice > 10) {
        cout << "Invalid input! Please try again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    return choice;
}
