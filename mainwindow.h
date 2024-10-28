#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Machine.h"

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

    void on_addInstructionBox_editingFinished();

    void on_clearMemoryButton_clicked();

    void on_addInstructionButton_clicked();

    void on_clearRegistersButton_clicked();

    void on_decodeButton_clicked();

    void on_executeButton_clicked();


private:
    Ui::VoleMachineSimulator *ui;
    Machine* machine;
    void initMemory();
    void initRegisters();
};
#endif // MAINWINDOW_H
