//
// Created by Adham Hamdy on 10/4/2024.
//

#ifndef VOLE_MACHINE_REGISTER_H
#define VOLE_MACHINE_REGISTER_H
#include <string>
using namespace std;

class Register {
private:
    string value;
public:
    explicit Register(const string& = "00");
    ~Register();
    void setValue(const string&);
    const string& getValue() const;
    void clear(const int&);

//Todo register = "00"
};


#endif //VOLE_MACHINE_REGISTER_H
