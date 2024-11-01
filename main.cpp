#include <iostream>
#include "Machine.h"

class MainUI{
private:
    Machine machine;
    bool enterFileOrInstructions;

public:
    bool getFileOrInstruction(){
        char choice;
        cout << "Enter input method (f for file, i for instructions): ";
        cin >> choice;
        enterFileOrInstructions = (choice == 'f' || choice == 'F');
        return enterFileOrInstructions;
    }
    void DisplayMenu() {
        cout << "---- Vole Machine Menu ----\n";
        cout << "1. Load File\n";
        cout << "2. Display Memory Status\n";
        cout << "3. Display Registers Status\n";
        cout << "4. Input Instruction into console\n";
        cout << "5. Exit\n";

    }
    string inputFileName() {
        string fileName;
        cout << "Enter the file name to load: ";
        cin >> fileName;
        return fileName;
    }
    string inputInstruction() {
        string instruction;
        cout << "Enter an instruction: ";
        cin.ignore();
        getline(cin, instruction);
        return instruction;
    }
    short int inputChoice() {
        short int choice;
        cout << "Choose an option: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 9) {
            cout << "Invalid input! Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            return -1;
        }
        return choice;
    }
};





int main() {
    Machine m;
    auto mem = m.memory;
    auto p = m.processor;
    MainUI main;
    bool run= true;
    while(run) {


        main.DisplayMenu();
        short int choice = main.inputChoice();
        if (choice == -1) {
            continue;
        }

        switch (choice) {
            case 1 : {

                string fileName = main.inputFileName();
                m.loadProgramFile(fileName);
                while(run){

                    cout<<"1-fetch \n";
                    cout<<"2-decode\n";
                    cout<<"3-execute\n";
                    cout<<"4-clear memory\n";
                    cout<<"5-clear registers\n";
                    cout<<"6-run one cycle\n";
                    cout<<"7-Display Registers Status\n";
                    cout<<"8-Display Memory Status\n";
                    cout<<"9-Exit\n";
                    short int input=main.inputChoice();
                    switch(input){
                        case 1:{
                            p->fetchInstruction(mem);
                            break;
                        }
                        case 2 :{
                            p->decodeInstruction();
                            break;
                        }
                        case 3 : {
                            if (p->executeInstruction(mem)== false){
                                run=false;
                            }
                            else{
                                p->executeInstruction(mem);
                            }
                            break;
                        }
                        case 4 :{
                            m.clearMemory();
                            break;
                        }
                        case 5 :{
                            p->clearRegister();
                            break;
                        }
                        case 6 :{
                            p->fetchInstruction(mem);
                            p->decodeInstruction();
                            if (p->executeInstruction(mem)==false){
                                run=false;
                            }
                            else{
                                p->executeInstruction(mem);
                            }

                            break;
                        }
                        case 7:{
                            p->displayRegisters();
                            break;
                        }
                        case 8:{
                            m.displayStatus();
                            break;
                        }
                        case  9:{
                            cout<<"Exiting\n";
                            run = false;
                            break;
                        }

                    }
                }
                if (p->executeInstruction(mem)== false){
                    run=false;
                }
                else{
                    run=true;
                }

                break;
            }
            case 2: {
                m.displayStatus();
                break;
            }
            case 3:{
                p->displayRegisters();
                break;
            }
            case 4: {// take instruction from console
                string instruction = main.inputInstruction();
                m.inputInstruction(instruction);
                while(run){

                    cout<<"1-fetch \n";
                    cout<<"2-decode\n";
                    cout<<"3-execute\n";
                    cout<<"4-clear memory\n";
                    cout<<"5-clear registers\n";
                    cout<<"6-run one cycle\n";
                    cout<<"7-Display Registers Status\n";
                    cout<<"8-Display Memory Status\n";
                    cout<<"9-Exit\n";
                    short int input=main.inputChoice();
                    switch(input){
                        case 1:{
                            p->fetchInstruction(mem);
                            break;
                        }
                        case 2 :{
                            p->decodeInstruction();
                            break;
                        }
                        case  3 :{
                            if (p->executeInstruction(mem)== false){
                                run=false;
                            }
                            else{
                                p->executeInstruction(mem);
                            }
                            break;
                        }
                        case  4 :{
                            m.clearMemory();
                            break;
                        }
                        case  5 :{
                            p->clearRegister();
                            break;
                        }
                        case  6 :{
                            p->fetchInstruction(mem);
                            p->decodeInstruction();
                            if (p->executeInstruction(mem)==false){
                                run=false;
                            }
                            else{
                                p->executeInstruction(mem);
                            }

                            break;
                        }
                        case 7:{
                            p->displayRegisters();
                            break;
                        }
                        case 8:{
                            m.displayStatus();
                            break;
                        }
                        case  9:{
                            cout<<"Exiting\n";
                            run = false;
                            break;
                        }


                    }

                }

                if (p->executeInstruction(mem)== false){
                    run=false;
                }
                else{
                    run=true;
                }

                break;
            }
            case 5 : { // Exit
                cout << "Exiting\n";
                run= false;
                break;
            }
            default:
                cout<<"Invalid Input Please try again\n";

        }
    }
    return 0;
}
