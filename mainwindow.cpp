#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <string>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>

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
    delete ui;
}

void MainWindow::on_fetchButton_clicked()
{
    machine->processor->fetchInstruction(machine->memory);

    std::string pcHex = ALU::decToHex(machine->processor->pc);
    ui->pcVeiwBox->setText(QString::fromStdString(pcHex));

    ui->decodeButton->setEnabled(true);
    ui->executeButton->setEnabled(false);
}

void MainWindow::initRegisters(){
    ui->registersTable->clearContents();

    ui->registersTable->verticalHeader()->setVisible(false);

    ui->registersTable->setColumnCount(5);

    ui->registersTable->setHorizontalHeaderLabels({"Address", "Binary", "Hex", "Int", "Floating"});

    ui->registersTable->setRowCount(16);

    ui->registersTable->setColumnWidth(0, 60);
    ui->registersTable->setColumnWidth(1, 100);
    ui->registersTable->setColumnWidth(2, 60);
    ui->registersTable->setColumnWidth(3, 40);
    ui->registersTable->setColumnWidth(4, 100);

    for (int i = 0; i < 16; ++i) {
        QString address = QString::number(i, 16).rightJustified(2, '0').toUpper();

        QString hexValue = QString::fromStdString(machine->processor->registers->getCell(i));

        QString binary = hexToBinary(hexValue);

        int intValue = ALU::hexToDec(hexValue.toStdString());

        float floatingValue = ALU::hexToFloat(hexValue.toStdString());

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

    ui->MainMemoryTable->setColumnWidth(0, 60);
    ui->MainMemoryTable->setColumnWidth(1, 100);
    ui->MainMemoryTable->setColumnWidth(2, 60);
    ui->MainMemoryTable->setColumnWidth(3, 40);
    ui->MainMemoryTable->setColumnWidth(4, 100);

    for (int i = 0; i < 256; ++i) {
        QString address = QString::number(i, 16).rightJustified(2, '0').toUpper();

        QString hexValue = QString::fromStdString(machine->memory->getCell(i));

        QString binary = hexToBinary(hexValue);

        int intValue = ALU::hexToDec(hexValue.toStdString());

        float floatingValue = ALU::hexToFloat(hexValue.toStdString());

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
    initMemory();
    if(!machine->running){
        QMessageBox::information(this, "Done", "The execution has been halted.");
    }

    if(machine->processor->ir[0] == '3' && machine->processor->ir.substr(2) == "00"){
        std::string storeMsg = machine->processor->cu->value;
        ui->screenBox->setText(QString::fromStdString(storeMsg));
    }
    if(machine->processor->ir[0]=='B'){
        std::string newPc=to_string(machine->processor->pc);
         ui->pcVeiwBox->setText(QString::fromStdString(newPc));
    }
}

QString MainWindow::hexToBinary(const QString& hex) {
    bool ok;
    int hexValue = hex.toInt(&ok, 16);
    return QString::number(hexValue, 2).rightJustified(8, '0');
}

// int MainWindow::hexToInt(const QString& hex) {
//     bool ok;
//     return hex.toInt(&ok, 16);
// }

// float MainWindow::hexToFloat(const QString& hex) {
//     bool ok;
//     int intValue = hex.toInt(&ok, 16);
//     return *reinterpret_cast<float*>(&intValue);
// }

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

// void MainWindow::on_pcVeiwBox_editingFinished()
// {
//     std::string value = ui->pcVeiwBox->text().toStdString();
//     bool isHEX = machine->processor->alu->isHex(value);
//     bool isINT = machine->processor->alu->isInt(value);

//     if(isHEX || isINT){
//         int x = machine->processor->alu->hexToDec(value);
//         bool inRange = (x >= 0 && x < 256);
//         if (inRange){
//             machine->processor->pc = x;
//         } else {
//             QMessageBox::warning(this, "Invalid Input", "Please Enter a value between [0, 255].");

//         }
//     }
//      else {
//         QMessageBox::warning(this, "Invalid Input", "Please Enter a numeric value between [0, 255].");
//     }
// }

void MainWindow::on_loadFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Text File", "", "Text Files (*.txt);;All Files (*.*)");

    if (!filePath.isEmpty()) {
        qDebug() << "Selected file:" << filePath;

        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();


        QFile file(filePath);
        if (file.size() == 0) {
            QMessageBox::warning(this, "Empty File", "The selected file is empty. Please select a different file.");
            return;
        }

        std::string stdFileName = fileName.toStdString();


        QString destinationPath = QDir::currentPath() + "/" + fileName;


        if (QFile::exists(destinationPath)) {

            if (!QFile::remove(destinationPath)) {
                qDebug() << "Failed to remove the existing file.";
                QMessageBox::warning(this, "File Error", "Failed to overwrite the existing file.");
                return;
            }
        }


        if (QFile::copy(filePath, destinationPath)) {
            qDebug() << "File copied successfully to:" << destinationPath;
        } else {
            qDebug() << "Failed to copy the file.";
            QMessageBox::warning(this, "File Error", "Failed to copy the file.");
            return;
        }

        machine->loadProgramFile(stdFileName);
        MainWindow::initMemory();

        QMessageBox::information(this, "Load Successful", "The file was loaded successfully.");
    }
}

void MainWindow::on_runOneCycleButton_clicked()
{
    MainWindow::on_fetchButton_clicked();
    MainWindow::on_decodeButton_clicked();
    MainWindow::on_executeButton_clicked();
}

void MainWindow::on_runUntillHaltButton_clicked()
{
    short i = 0;

    while (machine->running) {
        MainWindow::on_runOneCycleButton_clicked();
        if(i++ >= 256){
            QMessageBox::warning(this, "Memory limit reached", "The execution has reached the end of the memory.");
            ui->pcVeiwBox->setText("0");
            machine->processor->pc = 0;
            return;
        }
    }

    QMessageBox::information(this, "Done", "The execution has been halted.");

}

// void MainWindow::initAboutTab()
// {
//     QLabel *aboutLabel = new QLabel("Vole Machine Simulator\nVersion 1.0\nDeveloped by: [Your Name]\n"
//                                     "This simulator mimics the operations of a virtual machine processor.", ui->aboutTab);
//     aboutLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
//     aboutLabel->setWordWrap(true);

//     QVBoxLayout *layout = new QVBoxLayout(ui->aboutTab);
//     layout->addWidget(aboutLabel);
//     ui->aboutTab->setLayout(layout);
// }


void MainWindow::on_aboutButton_clicked()
{
    QMessageBox::about(this, "About Vole Machine Simulator",
                       "<h2>Vole Machine Simulator</h2>"
                       "<p>This simulator mimics the operations of a virtual machine processor.</p>"
                       "<p><b>Created by:</b><br>"
                       "Ahmed Attia - 20230027<br>"
                       "Adham Hamdy - 20230043<br>"
                       "Youssef Bahaa - 20230487</p>"
                       "<p><b>Assignment:</b> Assignment 1, Task 4 - Object-Oriented Programming (CS213)</p>"
                       "<p><b>Instructor:</b> Dr. Mohamed El-Ramly</p>"
                       "<p><b>College:</b> Faculty of Computers and Artificial Intelligence - Cairo University</p>"
                       "<p><b>Vole Machine Description:</b><br>Refer to CS111 materials and 'CS: An Overview' book for details on the Vole machine and language.</p>");

}


void MainWindow::on_enterPC_Button_clicked() {
    std::string value = ui->pcVeiwBox->text().toStdString();
    bool isHEX = machine->processor->alu->isHex(value);
    bool isINT = machine->processor->alu->isInt(value);

 if (isINT) {
        int x = std::stoi(value);
        bool inRange = (x >= 0 && x < 256);
        if (inRange) {
            machine->processor->pc = x;
            QMessageBox::information(this, "PC Updated", "PC is updated successfully.");
           

        } else {
            QMessageBox::warning(this, "Invalid Input", "Please enter a value between [0, 255].");
        }
    }

 else if (isHEX) {
     int x = machine->processor->alu->hexToDec(value);
     bool inRange = (x >= 0 && x < 256);
     if (inRange) {
         machine->processor->pc = x;
         QMessageBox::information(this, "PC Updated", "PC is updated successfully.");
       

     } else {
         QMessageBox::warning(this, "Invalid Input", "Please enter a value between [0, 255].");
     }
 }


    else {
        QMessageBox::warning(this, "Invalid Input", "Please enter a numeric value (hexadecimal or integer) between [0, 255].");
    }

}


