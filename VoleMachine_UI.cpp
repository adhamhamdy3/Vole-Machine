#include "VoleMachine_UI.h"
#include "ui_VoleMachine_UI.h"
#include <QMessageBox>
#include <string>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>
#include <QColor>
#include "Utilities.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VoleMachineSimulator)
    , machine(new Machine()),
    playTimer(new QTimer(this))
{
    ui->setupUi(this);

    ui->printASCIIButton->setChecked(true);
    ui->stopButton->setEnabled(false);
    ui->hexButton->setChecked(true);

    initRegisters();
    initMemory();
    haltCount = 0;

    connect(playTimer, &QTimer::timeout, this, &MainWindow::executeInstructionCycle);

}

MainWindow::~MainWindow()
{
    delete machine;
    delete ui;
    delete playTimer;
}

void MainWindow::on_fetchButton_clicked()
{
    haltCount += !machine->running;

    if(!tryToContinueAfterHalt()) return;

    if(machine->memoryLimitReached) return void (showMLR_Msg());

    machine->processor->fetchInstruction(machine->memory);

    QString IR = QString::fromStdString(machine->processor->ir);
    ui->IR_Box->setText(IR);

    updatePC();

    ui->decodeButton->setEnabled(true);
    ui->executeButton->setEnabled(false);

    initMemory();
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

        int intValue = Utilities::Conversions::hexToDec(hexValue.toStdString());

        float floatingValue = Utilities::Conversions::hexToFloat(hexValue.toStdString());

        QTableWidgetItem *addressItem = new QTableWidgetItem(address);
        addressItem->setTextAlignment(Qt::AlignCenter);
        addressItem->setFlags(addressItem->flags() & ~Qt::ItemIsEditable);
        ui->registersTable->setItem(i, 0, addressItem);

        QTableWidgetItem *binaryItem = new QTableWidgetItem(binary);
        binaryItem->setTextAlignment(Qt::AlignCenter);
        binaryItem->setFlags(binaryItem->flags() & ~Qt::ItemIsEditable);
        ui->registersTable->setItem(i, 1, binaryItem);

        QTableWidgetItem *hexItem = new QTableWidgetItem(hexValue);
        hexItem->setTextAlignment(Qt::AlignCenter);
        hexItem->setFlags(hexItem->flags() & ~Qt::ItemIsEditable);
        ui->registersTable->setItem(i, 2, hexItem);

        QTableWidgetItem *intItem = new QTableWidgetItem(QString::number(intValue));
        intItem->setTextAlignment(Qt::AlignCenter);
        intItem->setFlags(intItem->flags() & ~Qt::ItemIsEditable);
        ui->registersTable->setItem(i, 3, intItem);

        QTableWidgetItem *floatItem = new QTableWidgetItem(QString::number(floatingValue));
        floatItem->setTextAlignment(Qt::AlignCenter);
        floatItem->setFlags(floatItem->flags() & ~Qt::ItemIsEditable);
        ui->registersTable->setItem(i, 4, floatItem);
    }
    for (int i = 0; i < 16; ++i) {
        if(machine->processor->registers->getCell(i) != "00"){
            setRowColor(ui->registersTable, i, lightYellow, black);
        }
    }
    updatePC();
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

        int intValue = Utilities::Conversions::hexToDec(hexValue.toStdString());

        float floatingValue = Utilities::Conversions::hexToFloat(hexValue.toStdString());

        QTableWidgetItem *addressItem = new QTableWidgetItem(address);
        addressItem->setTextAlignment(Qt::AlignCenter);
        addressItem->setFlags(addressItem->flags() & ~Qt::ItemIsEditable);
        ui->MainMemoryTable->setItem(i, 0, addressItem);

        QTableWidgetItem *binaryItem = new QTableWidgetItem(binary);
        binaryItem->setTextAlignment(Qt::AlignCenter);
        binaryItem->setFlags(binaryItem->flags() & ~Qt::ItemIsEditable);
        ui->MainMemoryTable->setItem(i, 1, binaryItem);

        QTableWidgetItem *hexItem = new QTableWidgetItem(hexValue);
        hexItem->setTextAlignment(Qt::AlignCenter);
        ui->MainMemoryTable->setItem(i, 2, hexItem);

        QTableWidgetItem *intItem = new QTableWidgetItem(QString::number(intValue));
        intItem->setTextAlignment(Qt::AlignCenter);
        intItem->setFlags(intItem->flags() & ~Qt::ItemIsEditable);
        ui->MainMemoryTable->setItem(i, 3, intItem);

        QTableWidgetItem *floatItem = new QTableWidgetItem(QString::number(floatingValue));
        floatItem->setTextAlignment(Qt::AlignCenter);
        floatItem->setFlags(floatItem->flags() & ~Qt::ItemIsEditable);
        ui->MainMemoryTable->setItem(i, 4, floatItem);
    }
    for (int i = 0; i < 256; ++i) {
        if (machine->processor->ir[0] == '3' && machine->processor->ir.substr(2) == "00") {
            setRowColor(ui->MainMemoryTable, 0, lightCyan, black);
        }

        if (machine->memory->getCell(i) == "C0") {
            setRowColor(ui->MainMemoryTable, i, red, black);
            if (i + 1 < 256) {
                setRowColor(ui->MainMemoryTable, i + 1, red, black);
            }
        }
        else if (machine->memory->getCell(i) != "00") {
            setRowColor(ui->MainMemoryTable, i, lightYellow, black);
            if (i + 1 < 256) {
                setRowColor(ui->MainMemoryTable, i + 1, lightYellow, black);
            }
        }
    }
    updatePC();
}

void MainWindow::on_clearRegistersButton_clicked()
{
    QMessageBox::StandardButton clear = QMessageBox::question(this, "Clear Registers",
                                       "Are you sure about clearing all the registers?",
                                       QMessageBox::Yes | QMessageBox::No);

    if(clear == QMessageBox::Yes){
        machine->processor->clearRegister();
        initRegisters();
        initMemory();
    }
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
        ui->OP_Box->setText("0");
        ui->RBox->setText("0");
        ui->XBox->setText("0");
        ui->YBox->setText("0");
        break;
    }
    case '1': case '2': case '3': case 'B':{

        ui->RLabel->setText("R:");
        ui->XLabel->setText("X:");
        ui->YLabel->setText("Y:");

        setDecodeLabels(IR[0], IR[1], IR[2], IR[3]);
        break;
    }
    case '4':{
        ui->RLabel->setText("?:");
        ui->XLabel->setText("R:");
        ui->YLabel->setText("S:");

        setDecodeLabels(IR[0], IR[1], IR[2], IR[3]);

        break;
    }
    case '5': case '6': case '7': case '8': case '9': {

        ui->RLabel->setText("R:");
        ui->XLabel->setText("S:");
        ui->YLabel->setText("T:");

        setDecodeLabels(IR[0], IR[1], IR[2], IR[3]);

        break;
    }
    case 'A':{

        ui->RLabel->setText("?");
        ui->XLabel->setText("S:");
        ui->YLabel->setText("T:");

        setDecodeLabels(IR[0], IR[1], IR[2], IR[3]);

        break;
    }
    case 'C':{
        ui->RLabel->setText("?:");
        ui->XLabel->setText("?:");
        ui->YLabel->setText("?:");

        setDecodeLabels(IR[0], IR[1], IR[2], IR[3]);

        break;
    }
    case 'D':{
        ui->RLabel->setText("R:");
        ui->XLabel->setText("X:");
        ui->YLabel->setText("Y:");

        setDecodeLabels(IR[0], IR[1], IR[2], IR[3]);

        break;
    }
    }
    ui->executeButton->setEnabled(true);
}

void MainWindow::on_executeButton_clicked()
{
    if(!machine->running && haltCount == 1){
        QMessageBox::information(this, "Done", "The execution has been halted.");

    } else{
        machine->processor->executeInstruction(machine->memory);

        initRegisters();
        initMemory();

        if(machine->processor->ir[0] == '3' && machine->processor->ir.substr(2) == "00"){

            if(ui->printASCIIButton->isChecked()){

                ui->screenBox->setText(QString::fromStdString(machine->processor->cu->ASCIIstr));

            } else {

                ui->screenBox->setText(QString::fromStdString(machine->processor->cu->HEXstr));

            }

        }
    }

    updatePC();
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

    bool valid = Utilities::Validations::isValid(instructionStr);

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
    machine->processor->cu->ASCIIstr = "", machine->processor->cu->HEXstr = "";
}

void MainWindow::on_clearMemoryButton_clicked()
{

    QMessageBox::StandardButton clear = QMessageBox::question(this, "Clear Memory",
                                                              "Are you sure about clearing all the memory cells?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (clear == QMessageBox::Yes) {
        machine->clearMemory();
        initMemory();
    }
}

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

void MainWindow::on_runUntilHaltButton_clicked()
{
    while (machine->running) {
        MainWindow::on_runOneCycleButton_clicked();
        if(machine->memoryLimitReached) return void(showMLR_Msg());
    }
    QMessageBox::information(this, "Done", "The execution has been halted.");
}

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

void MainWindow::setRowColor(QTableWidget *tableWidget, int row, const QColor& color, const QColor& tColor) {
    for (int col = 0; col < tableWidget->columnCount(); ++col) {
        tableWidget->item(row, col)->setBackground(color);
        tableWidget->item(row, col)->setForeground(tColor);

    }
}

void MainWindow::on_printASCIIButton_clicked()
{
    ui->printHEXButton->setChecked(false);
    ui->screenBox->setText(QString::fromStdString(machine->processor->cu->ASCIIstr));
    updatePC();
}


void MainWindow::on_printHEXButton_clicked()
{
    ui->printASCIIButton->setChecked(false);
    ui->screenBox->setText(QString::fromStdString(machine->processor->cu->HEXstr));

    updatePC();
}


void MainWindow::on_stAdrsBox_returnPressed()
{
    if (ui->stAdrsBox->text().isEmpty())
        return;

    std::string newAddress = ui->stAdrsBox->text().toStdString();

    Utilities::Conversions::toUpper(newAddress);

    if (Utilities::Validations::isValid_memAddress(newAddress)) {
        machine->setStartingAddress(newAddress);
        QMessageBox::information(this,"Memory Starting Address Updated",
                                 "Memory Starting Address Updated to: " +
                                     QString::fromStdString(newAddress));

        initMemory();
        updatePC();

        ui->MainMemoryTable->scrollToItem(ui->MainMemoryTable->item(machine->processor->pc, 0),
                                          QAbstractItemView::PositionAtCenter);
    } else {
        QMessageBox::warning(this, "Invalid Address",
                             "Invalid memory address! "
                             "Please enter a valid hexadecimal number ranging between [0, 255] in decimal.");
    }
}

void MainWindow::updatePC(){
    if(ui->hexButton->isChecked()){
        std::string pcHex = Utilities::Conversions::decToHex(machine->processor->pc);
        ui->pcVeiwBox->setText(QString::fromStdString(pcHex));
    } else {
        ui->pcVeiwBox->setText(QString::fromStdString(std::to_string(machine->processor->pc)));
    }
    setRowColor(ui->MainMemoryTable, machine->processor->pc, lightGreen, black);
}

bool MainWindow::tryToContinueAfterHalt(){
    if(haltCount > 1){
        QMessageBox::StandardButton continueExe = QMessageBox::question(this, "Instruction Halted",
                                                                        "The last performed instruction resulted in a halt"
                                                                        " to the execution of the program. Are you"
                                                                        " want to perform the next operation?",
                                                                        QMessageBox::Yes | QMessageBox::No);

        machine->running = (continueExe == QMessageBox::Yes);
        if(continueExe == QMessageBox::Yes){
            machine->running = true;
            haltCount = 0;
            return true;
        }
    }

    return machine->running;
}



void MainWindow::on_playButton_clicked()
{
    int instructionsPerSecond = ui->instructionPerSec->value();

    playTimer->start(1000 / instructionsPerSecond);

    ui->playButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}


void MainWindow::executeInstructionCycle()
{
    if (!machine->running) {
        playTimer->stop();
        QMessageBox::information(this, "Execution Halted", "The program has halted.");
        ui->playButton->setEnabled(true);
        ui->stopButton->setEnabled(false);
        return;
    }

    else if (machine->memoryLimitReached) {
        showMLR_Msg();
        playTimer->stop();
        ui->playButton->setEnabled(true);
        ui->stopButton->setEnabled(false);
        return;
    }

    MainWindow::on_playButton_clicked(); // update speed
    MainWindow::on_runOneCycleButton_clicked();

    int pcRow = machine->processor->pc;
    ui->MainMemoryTable->scrollToItem(ui->MainMemoryTable->item(pcRow, 0), QAbstractItemView::PositionAtCenter);
}

void MainWindow::on_stopButton_clicked()
{
    playTimer->stop();
    ui->playButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}

void MainWindow::showMLR_Msg(){
    QMessageBox::warning(this, "Memory limit reached",
                         "The execution has reached the end of the memory, PC is reset to 0A");

    //machine->processor->pc = 10;

    updatePC();
    initMemory();

    machine->memoryLimitReached = false;
}

void MainWindow::setDecodeLabels(const QString &A, const QString &B, const QString &C, const QString &D){
    ui->OP_Box->setText(A);

    ui->RBox->setText(B);

    ui->XBox->setText(C);

    ui->YBox->setText(D);
}

void MainWindow::on_MainMemoryTable_cellEntered(int row, int column)
{
    if(column != 2) return;

    QString cellHexValue = ui->MainMemoryTable->item(row, column)->text();

    machine->memory->setCell(row, cellHexValue.toStdString());

    QString binary = hexToBinary(cellHexValue);
    int intValue = Utilities::Conversions::hexToDec(cellHexValue.toStdString());
    float floatingValue = Utilities::Conversions::hexToFloat(cellHexValue.toStdString());

    ui->MainMemoryTable->item(row, 1)->setText(binary);
    ui->MainMemoryTable->item(row, 3)->setText(QString::number(intValue));
    ui->MainMemoryTable->item(row, 4)->setText(QString::number(floatingValue));
    initMemory();
}


void MainWindow::on_pcVeiwBox_returnPressed()
{
    std::string value = ui->pcVeiwBox->text().toStdString();
    // bool isHEX = Utilities::Validations::isHex(value);
    // bool isINT = Utilities::Validations::isInt(value);

    bool INT_MODE = ui->intButton->isChecked();
    bool HEX_MODE = ui->hexButton->isChecked();

    if (INT_MODE) {
        ui->pcVeiwBox->setMaxLength(3);
        int x = std::stoi(value);
        bool inRange = (x >= 0 && x < 256);
        if (inRange) {
            machine->processor->pc = x;
            QMessageBox::information(this, "PC Updated", "PC is updated successfully.");
            Machine::running = true;

        } else {
            QMessageBox::warning(this, "Invalid Input", "Please enter a value between [0, 255].");
        }
        updatePC();
    }

    else if (HEX_MODE) {
        ui->pcVeiwBox->setMaxLength(2);
        int x = Utilities::Conversions::hexToDec(value);
        bool inRange = (x >= 0 && x < 256);
        if (inRange) {
            machine->processor->pc = x;
            QMessageBox::information(this, "PC Updated", "PC is updated successfully.");
            Machine::running = true;

        } else {
            QMessageBox::warning(this, "Invalid Input", "Please enter a value between [0, 255].");
        }
        updatePC();
    }


    else {
        QMessageBox::warning(this, "Invalid Input", "Please enter a numeric value (hexadecimal or integer) between [0, 255].");
    }
    initMemory();
    // ui->MainMemoryTable->scrollToItem(ui->MainMemoryTable->item(machine->processor->pc, 0),
    //                                   QAbstractItemView::PositionAtCenter);
}


void MainWindow::on_hexButton_clicked()
{
    updatePC();
}


void MainWindow::on_intButton_clicked()
{
    updatePC();
}


void MainWindow::on_resetPC_Button_clicked()
{
    machine->processor->pc = 10;
    updatePC();
    int pcRow = machine->processor->pc;
    ui->MainMemoryTable->scrollToItem(ui->MainMemoryTable->item(pcRow, 0),
                                      QAbstractItemView::PositionAtCenter);
}


void MainWindow::on_helpButton_clicked()
{
    QString helpText = R"(
    <b>VOLE Instructions</b>
    <table border='1' cellspacing='0' cellpadding='5' style="border-collapse: collapse; width: 100%;">
    <tr>
        <th style="text-align: center;">Op-code</th>
        <th style="text-align: center;">Operand</th>
        <th>Description</th>
    </tr>
    <tr>
        <td style="text-align: center;">1</td>
        <td style="text-align: center;">RXY</td>
        <td>LOAD the register R with the bit pattern found in the memory cell whose address is XY.</td>
    </tr>
    <tr>
        <td style="text-align: center;">2</td>
        <td style="text-align: center;">RXY</td>
        <td>LOAD the register R with the bit pattern XY.</td>
    </tr>
    <tr>
        <td style="text-align: center;">3</td>
        <td style="text-align: center;">RXY</td>
        <td>STORE the bit pattern found in register R in the memory cell whose address is XY.</td>
    </tr>
    <tr>
        <td style="text-align: center;">3</td>
        <td style="text-align: center;">R00</td>
        <td>STORE to location 00, which is a memory mapping for the screen. Writing to 00 is writing to screen.</td>
    </tr>
    <tr>
        <td style="text-align: center;">4</td>
        <td style="text-align: center;">0RS</td>
        <td>MOVE the bit pattern found in register R to register S.</td>
    </tr>
    <tr>
        <td style="text-align: center;">5</td>
        <td style="text-align: center;">RST</td>
        <td>ADD the bit patterns in registers S and T (two's complement) and leave the result in register R.</td>
    </tr>
    <tr>
        <td style="text-align: center;">6</td>
        <td style="text-align: center;">RST</td>
        <td>ADD the bit patterns in registers S and T (floating-point) and leave the result in register R.</td>
    </tr>
    <tr>
        <td style="text-align: center;">7</td>
        <td style="text-align: center;">RST</td>
        <td>OR the bit patterns in registers S and T and place the result in register R.</td>
    </tr>
    <tr>
        <td style="text-align: center;">8</td>
        <td style="text-align: center;">RST</td>
        <td>AND the bit patterns in registers S and T and place the result in register R.</td>
    </tr>
    <tr>
        <td style="text-align: center;">9</td>
        <td style="text-align: center;">RST</td>
        <td>EXCLUSIVE OR the bit patterns in registers S and T and place the result in register R.</td>
    </tr>
    <tr>
        <td style="text-align: center;">A</td>
        <td style="text-align: center;">xRX</td>
        <td>ROTATE the bit pattern in register R one bit to the right X times.</td>
    </tr>
    <tr>
        <td style="text-align: center;">B</td>
        <td style="text-align: center;">RXY</td>
        <td>JUMP to instruction located in memory cell at XY if register R equals register 0.</td>
    </tr>
    <tr>
        <td style="text-align: center;">C</td>
        <td style="text-align: center;">000</td>
        <td>HALT execution.</td>
    </tr>
    <tr>
        <td style="text-align: center;">D</td>
        <td style="text-align: center;">RXY</td>
        <td>JUMP to instruction in memory cell XY if register R &gt; register 0.</td>
    </tr>
</table>

<hr>
<b>Vole Machine App Color Code</b>
<table border='1' cellspacing='0' cellpadding='5' style="border-collapse: collapse; width: 100%;">
    <tr>
        <th style="text-align: left;">Color</th>
        <th>Description</th>
    </tr>
    <tr>
        <td style="background-color: lightyellow; text-align: center; color: black;">Light Yellow</td>
        <td>Recently added value to a cell in eihter memory or registers.</td>
    </tr>
    <tr>
        <td style="background-color: lightgreen; text-align: center; color: black;">Light Green</td>
        <td>PC (Program Counter) location in memory.</td>
    </tr>
    <tr>
        <td style="background-color: red; text-align: center; color: black;">Light Red</td>
        <td>Halt location in memory.</td>
    </tr>
    <tr>
        <td style="background-color: lightcyan; text-align: center; vertical-align: middle; color: black;">Light Cyan</td>
        <td>Recently added value to the cell 00 in memory, where the screen operation occurs.</td>
    </tr>
</table>
;
<hr>
<b>GitHub Repository</b><br>
For more details and the source code, visit:
<a href='https://github.com/adhamhamdy3/Vole-Machine' style="color: blue; text-decoration: none;"><b>Vole-Machine Repository</b></a>
)";

    QMessageBox helpDialog;
    helpDialog.setWindowTitle("Vole Machine Help");
    helpDialog.setText(helpText);
    helpDialog.setIcon(QMessageBox::Information);
    helpDialog.setStandardButtons(QMessageBox::Ok);
    helpDialog.exec();
}

void MainWindow::on_MainMemoryTable_cellClicked(int row, int column)
{
    machine->processor->pc = row;
    initMemory();
    updatePC();
}

