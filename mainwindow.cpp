#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VoleMachineSimulator)
    , machine(new Machine())
{
    ui->setupUi(this);
    ui->pcVeiwBox->setText("0");
    initMemory();
    initRegisters();
}

MainWindow::~MainWindow()
{
    delete machine;
    delete ui;
}

void MainWindow::on_fetchButton_clicked()
{
    machine->processor->fetchInstruction(machine->memory);
    std::string pc = to_string(machine->processor->pc);
    ui->pcVeiwBox->setText(QString::fromStdString(pc));
}

void MainWindow::initMemory(){
    ui->memoryList->clear();

    for (int i = 0; i < 256; ++i) {
        ui->memoryList->addItem(QString::fromStdString(machine->memory->getCell(i)));
    }
}

void MainWindow::initRegisters(){
    ui->registersList->clear();

    for (int i = 0; i < 16; ++i) {
        ui->registersList->addItem(QString::fromStdString(machine->processor->registers->getCell(i)));
    }
}


void MainWindow::on_addInstructionBox_editingFinished()
{
    QString instruction = ui->addInstructionBox->text();
    std::string instructionStr = instruction.toStdString();

    bool valid = machine->processor->alu->isValid(instructionStr);

    if (!ui->addInstructionBox->text().isEmpty() && valid) {

        std::string inst = instruction.toStdString();

        machine->inputInstruction(inst);

        initMemory();
    } else {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid instruction.");
    }
}


void MainWindow::on_clearMemoryButton_clicked()
{
    machine->clearMemory();

    initMemory();
}


void MainWindow::on_clearRegistersButton_clicked()
{
    machine->processor->clearRegister();

    initRegisters();
}


void MainWindow::on_addInstructionButton_clicked()
{
    QString instruction = ui->addInstructionBox->text();
    std::string instructionStr = instruction.toStdString();

    bool valid = machine->processor->alu->isValid(instructionStr);

    if (!ui->addInstructionBox->text().isEmpty() && valid) {

        std::string inst = instruction.toStdString();

        machine->inputInstruction(inst);

        initMemory();
    } else {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid instruction.");
    }
}






void MainWindow::on_decodeButton_clicked()
{
    machine->processor->decodeInstruction();
    std::string msg = machine->processor->decodeMessage;
    QString decodeMsg = QString::fromStdString(msg);

    ui->decodeMessage->setText(decodeMsg);
}


void MainWindow::on_executeButton_clicked()
{
    machine->processor->executeInstruction(machine->memory);
    initMemory();
    initRegisters();

    if(machine->processor->ir[0] == '3' && machine->processor->ir.substr(2) == "00"){
        std::string storeMsg = machine->processor->cu->value;
        ui->screenBox->setText(QString::fromStdString(storeMsg));
    }
}
// some issue in instruction 3R00,, check the .exe Simulator


