#ifndef VOLE_MACHINE_REGISTER_H
#define VOLE_MACHINE_REGISTER_H

#include <iostream>
#include <stdexcept>

using namespace std;

class Register {
private:
    string registers[16];
public:
    Register();
    void setCell(const int&, const string&);
    string getCell(const int&) const;
};


#endif //VOLE_MACHINE_REGISTER_H
