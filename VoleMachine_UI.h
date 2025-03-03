#ifndef VOLEMACHINE_UI_H
#define VOLEMACHINE_UI_H

#include <QMainWindow>
#include "Machine.h"
#include <QTableWidget>
#include <QTimer>

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

    void on_runUntilHaltButton_clicked();

    void on_aboutButton_clicked();

    void on_printASCIIButton_clicked();

    void on_printHEXButton_clicked();

    void on_stAdrsBox_returnPressed();

    void on_playButton_clicked();

    void on_stopButton_clicked();

    void on_MainMemoryTable_cellEntered(int row, int column);

    void on_pcVeiwBox_returnPressed();

    void on_hexButton_clicked();

    void on_intButton_clicked();

    void on_resetPC_Button_clicked();

    void on_helpButton_clicked();

    void on_MainMemoryTable_cellClicked(int row, int column);

private:
    Ui::VoleMachineSimulator *ui;
    Machine* machine;
    QTimer* playTimer;

    void initRegisters();
    void initMemory();

    void initAboutTab();

    void updatePC();

    QString hexToBinary(const QString&);
    // int hexToInt(const QString&);
    // float hexToFloat(const QString&);

    QColor lightGreen = QColor(144, 238, 144);
    QColor lightYellow = QColor(255, 255, 224);
    QColor red = QColor(244, 67, 54);
    QColor white = QColor(255, 255, 255);
    QColor black = QColor(0, 0, 0);
    QColor lightCyan = QColor(224, 255, 255);


    void setRowColor(QTableWidget *tableWidget, int row, const QColor& color, const QColor& tColor);

    int haltCount;
    bool tryToContinueAfterHalt();
    void executeInstructionCycle();
    void showMLR_Msg();
    void setDecodeLabels(const QString&, const QString&, const QString&, const QString&);
};
#endif // VOLEMACHINE_UI_H
