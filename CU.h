//
// Created by power on 10/6/2024.
//

#ifndef VOLE_MACHINE_CU_H
#define VOLE_MACHINE_CU_H


class VoleMachine;
class CU {
public:
    static void load1(VoleMachine*);
    static void load2(VoleMachine*);
    static void store1(VoleMachine*);
    static void store2(VoleMachine*);
    static void move(VoleMachine*);
    static void add1(VoleMachine*);
    static void add2(VoleMachine*);
    static void jump(VoleMachine*);

};


#endif //VOLE_MACHINE_CU_H
