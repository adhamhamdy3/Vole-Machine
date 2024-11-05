#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Machine.h"
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class VoleMachineSimulator;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fetchButton_clicked();

    void on_clearRegistersButton_clicked();

    void on_decodeButton_clicked();

    void on_executeButton_clicked();

    void on_addInstructionButton_clicked();

    void on_clearScreenButton_clicked();

    void on_clearMemoryButton_clicked();

    void on_loadFileButton_clicked();

    void on_runOneCycleButton_clicked();

    void on_runUntillHaltButton_clicked();

    void on_aboutButton_clicked();

    void on_enterPC_Button_clicked();

private:
    Ui::VoleMachineSimulator *ui;
    Machine* machine;
    void initRegisters();
    void initMemory();

    void initAboutTab();

    QString hexToBinary(const QString&);
    // int hexToInt(const QString&);
    // float hexToFloat(const QString&);


    void setRowColor(QTableWidget *tableWidget, int row);
};
#endif // MAINWINDOW_H
