#ifndef VOLE_MACHINE_MEMORY_H
#define VOLE_MACHINE_MEMORY_H

#include <stdexcept>
#include <iostream>

using namespace std;

class Memory {
private:
    string memory[256];
public:
    Memory();
    void setCell(const int&, const string&);
    string getCell(const int&) const;
};


#endif //VOLE_MACHINE_MEMORY_H
