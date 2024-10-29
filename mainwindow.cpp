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
    initRegisters();
    initMemory();
}

MainWindow::~MainWindow()
{
    delete machine;
    delete ui->MainMemoryTable;
    delete ui;
}

void MainWindow::on_fetchButton_clicked()
{
    machine->processor->fetchInstruction(machine->memory);
    std::string pc = to_string(machine->processor->pc);
    ui->pcVeiwBox->setText(QString::fromStdString(pc));
    ui->decodeButton->setEnabled(true);
    ui->executeButton->setEnabled(false);
}


void MainWindow::initRegisters(){
    ui->registersTable->clearContents();

    ui->registersTable->verticalHeader()->setVisible(false);

    ui->registersTable->setColumnCount(5);

    ui->registersTable->setHorizontalHeaderLabels({"Address", "Binary", "Hex", "Int", "Floating"});

    ui->registersTable->setRowCount(16);

    ui->registersTable->setColumnWidth(0, 60);  // Address
    ui->registersTable->setColumnWidth(1, 100); // Binary
    ui->registersTable->setColumnWidth(2, 60);  // Hex
    ui->registersTable->setColumnWidth(3, 40);  // Int
    ui->registersTable->setColumnWidth(4, 100);  // Floating

    for (int i = 0; i < 16; ++i) {
        // Address in hexadecimal format
        QString address = QString::number(i, 16).rightJustified(2, '0').toUpper();

        // Hexadecimal value from memory array
        QString hexValue = QString::fromStdString(machine->processor->registers->getCell(i));  // Replace machine->memory with your actual memory array reference

        // Binary value converted from hex
        QString binary = hexToBinary(hexValue);

        // Integer value converted from hex
        int intValue = hexToInt(hexValue);

        // Floating-point value converted from hex
        float floatingValue = hexToFloat(hexValue);

        // Populate table cells
        // Populate table cells and set text alignment to center
        QTableWidgetItem *addressItem = new QTableWidgetItem(address);
        addressItem->setTextAlignment(Qt::AlignCenter);
        ui->registersTable->setItem(i, 0, addressItem);

        QTableWidgetItem *binaryItem = new QTableWidgetItem(binary);
        binaryItem->setTextAlignment(Qt::AlignCenter);
        ui->registersTable->setItem(i, 1, binaryItem);

        QTableWidgetItem *hexItem = new QTableWidgetItem(hexValue);
        hexItem->setTextAlignment(Qt::AlignCenter);
        ui->registersTable->setItem(i, 2, hexItem);

        QTableWidgetItem *intItem = new QTableWidgetItem(QString::number(intValue));
        intItem->setTextAlignment(Qt::AlignCenter);
        ui->registersTable->setItem(i, 3, intItem);

        QTableWidgetItem *floatItem = new QTableWidgetItem(QString::number(floatingValue));
        floatItem->setTextAlignment(Qt::AlignCenter);
        ui->registersTable->setItem(i, 4, floatItem);
    }
}


void MainWindow::initMemory(){
    ui->MainMemoryTable->clearContents();

    ui->MainMemoryTable->verticalHeader()->setVisible(false);

    ui->MainMemoryTable->setColumnCount(5);

    ui->MainMemoryTable->setHorizontalHeaderLabels({"Address", "Binary", "Hex", "Int", "Floating"});

    ui->MainMemoryTable->setRowCount(256);

    ui->MainMemoryTable->setColumnWidth(0, 60);  // Address
    ui->MainMemoryTable->setColumnWidth(1, 100); // Binary
    ui->MainMemoryTable->setColumnWidth(2, 60);  // Hex
    ui->MainMemoryTable->setColumnWidth(3, 40);  // Int
    ui->MainMemoryTable->setColumnWidth(4, 100);  // Floating

    for (int i = 0; i < 256; ++i) {
        // Address in hexadecimal format
        QString address = QString::number(i, 16).rightJustified(2, '0').toUpper();

        // Hexadecimal value from memory array
        QString hexValue = QString::fromStdString(machine->memory->getCell(i));  // Replace machine->memory with your actual memory array reference

        // Binary value converted from hex
        QString binary = hexToBinary(hexValue);

        // Integer value converted from hex
        int intValue = hexToInt(hexValue);

        // Floating-point value converted from hex
        float floatingValue = hexToFloat(hexValue);

        // Populate table cells
        // Populate table cells and set text alignment to center
        QTableWidgetItem *addressItem = new QTableWidgetItem(address);
        addressItem->setTextAlignment(Qt::AlignCenter);
        ui->MainMemoryTable->setItem(i, 0, addressItem);

        QTableWidgetItem *binaryItem = new QTableWidgetItem(binary);
        binaryItem->setTextAlignment(Qt::AlignCenter);
        ui->MainMemoryTable->setItem(i, 1, binaryItem);

        QTableWidgetItem *hexItem = new QTableWidgetItem(hexValue);
        hexItem->setTextAlignment(Qt::AlignCenter);
        ui->MainMemoryTable->setItem(i, 2, hexItem);

        QTableWidgetItem *intItem = new QTableWidgetItem(QString::number(intValue));
        intItem->setTextAlignment(Qt::AlignCenter);
        ui->MainMemoryTable->setItem(i, 3, intItem);

        QTableWidgetItem *floatItem = new QTableWidgetItem(QString::number(floatingValue));
        floatItem->setTextAlignment(Qt::AlignCenter);
        ui->MainMemoryTable->setItem(i, 4, floatItem);
    }

}





void MainWindow::on_clearRegistersButton_clicked()
{
    machine->processor->clearRegister();

    initRegisters();
    initMemory();
}








void MainWindow::on_decodeButton_clicked()
{
    machine->processor->decodeInstruction();
    std::string msg = machine->processor->decodeMessage;
    QString decodeMsg = QString::fromStdString(msg);

    ui->decodeMessage->setText(decodeMsg);

    QString IR = QString::fromStdString(machine->processor->ir);
    std::string stdStrIR = machine->processor->ir;

    switch (stdStrIR[0]) {
    case '0':{
        ui->IR_Box->setText(IR);
        ui->OP_Box->setText("0");
        ui->RBox->setText("0");
        ui->XBox->setText("0");
        ui->YBox->setText("0");
        break;
    }
    case '1': case '2': case '3': case 'B':{
        ui->IR_Box->setText(IR);
        ui->OP_Box->setText(IR[0]);

        ui->RBox->setText(IR[1]);
        ui->RLabel->setText("R:");

        ui->XBox->setText(IR[2]);
        ui->XLabel->setText("X:");


        ui->YBox->setText(IR[3]);
        ui->YLabel->setText("Y:");
        break;
    }
    case '4':{
        ui->IR_Box->setText(IR);
        ui->OP_Box->setText(IR[0]);

        ui->RBox->setText(IR[1]);
        ui->RLabel->setText("?:");

        ui->XBox->setText(IR[2]);
        ui->XLabel->setText("R:");


        ui->YBox->setText(IR[3]);
        ui->YLabel->setText("S:");
        break;
    }
    case '5': case '6':{
        ui->IR_Box->setText(IR);
        ui->OP_Box->setText(IR[0]);

        ui->RBox->setText(IR[1]);
        ui->RLabel->setText("R:");

        ui->XBox->setText(IR[2]);
        ui->XLabel->setText("S:");


        ui->YBox->setText(IR[3]);
        ui->YLabel->setText("T:");
        break;
    }
    case 'C':{
        ui->IR_Box->setText(IR);
        ui->OP_Box->setText(IR[0]);

        ui->RBox->setText(IR[1]);
        ui->RLabel->setText("?:");

        ui->XBox->setText(IR[2]);
        ui->XLabel->setText("?:");


        ui->YBox->setText(IR[3]);
        ui->YLabel->setText("?:");
        break;
    }
    }
    ui->executeButton->setEnabled(true);
}


void MainWindow::on_executeButton_clicked()
{
    machine->processor->executeInstruction(machine->memory);
    initRegisters();

    if(machine->processor->ir[0] == '3' && machine->processor->ir.substr(2) == "00"){
        std::string storeMsg = machine->processor->cu->value;
        ui->screenBox->setText(QString::fromStdString(storeMsg));
    }
}
// some issue in instruction 3R00,, check the .exe Simulator


// Convert hex string to binary string
QString MainWindow::hexToBinary(const QString& hex) {
    bool ok;
    int hexValue = hex.toInt(&ok, 16);  // Convert hex to integer
    return QString::number(hexValue, 2).rightJustified(8, '0');  // Convert to binary and pad to 8 bits
}

// Convert hex string to integer
int MainWindow::hexToInt(const QString& hex) {
    bool ok;
    return hex.toInt(&ok, 16);  // Convert hex to integer
}

// Convert hex string to floating point
float MainWindow::hexToFloat(const QString& hex) {
    bool ok;
    int intValue = hex.toInt(&ok, 16);  // Convert hex to integer
    return *reinterpret_cast<float*>(&intValue);  // Interpret the integer bits as a float
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


void MainWindow::on_clearScreenButton_clicked()
{
    ui->screenBox->clear();
}



void MainWindow::on_clearMemoryButton_clicked()
{

    machine->clearMemory();

    initMemory();

}


void MainWindow::on_pcVeiwBox_editingFinished()
{
    std::string value = ui->pcVeiwBox->text().toStdString();
    bool isHEX = machine->processor->alu->isHex(value);
    bool isINT = machine->processor->alu->isInt(value);

    if(isHEX || isINT){
        int x = machine->processor->alu->hexToDec(value);
        bool inRange = (x >= 0 && x < 256);
        if (inRange){
            machine->processor->pc = x;
        } else {
            QMessageBox::warning(this, "Invalid Input", "Please Enter a value between [0, 255].");

        }
    }
     else {
        QMessageBox::warning(this, "Invalid Input", "Please Enter a numeric value between [0, 255].");
    }
}

