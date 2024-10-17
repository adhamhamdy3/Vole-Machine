#include "VoleMachine.h"
#include <iostream>
using namespace std;
int main() {
    VoleMachine vmachine;
    vmachine.loadProgram("file.txt");
       do {
        vmachine.fetchInstruction();
        vmachine.executeInstruction();
      } while (vmachine.executeInstruction());
      cout << "==============================================================" << endl;
   // vmachine.memoryManager.displayMemory();
   //vmachine.displayRegisters();


    return 0;
}
