#include <iostream>
#include "Machine.h"

int main() {
    Machine m;
    auto mem = m.memory;
    auto p = m.processor;
    m.loadProgramFile("file.txt");
    m.displayStatus();
    cout << endl;

    while (m.running){
        p->fetchInstruction(mem);
        p->executeInstruction(mem);
    }
    cout << endl;

    m.displayStatus();
    cout << endl;
    p->displayRegisters();
    return 0;
}
