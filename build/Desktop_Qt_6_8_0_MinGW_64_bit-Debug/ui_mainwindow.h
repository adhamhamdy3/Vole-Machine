/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VoleMachineSimulator
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addInstructionButton;
    QPushButton *clearMemoryButton;
    QPushButton *Exit;
    QTextEdit *decodeMessage;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *RegistersLabel;
    QListWidget *registersList;
    QPushButton *clearRegistersButton;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *PC_Label;
    QLineEdit *pcVeiwBox;
    QPushButton *fetchButton;
    QPushButton *decodeButton;
    QPushButton *executeButton;
    QWidget *widget3;
    QVBoxLayout *verticalLayout;
    QLabel *MainMemoryLabel;
    QListWidget *memoryList;
    QLabel *addInstructionLabel;
    QLineEdit *addInstructionBox;
    QWidget *widget4;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QTextEdit *screenBox;
    QMenuBar *menubar;
    QMenu *menua;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *VoleMachineSimulator)
    {
        if (VoleMachineSimulator->objectName().isEmpty())
            VoleMachineSimulator->setObjectName("VoleMachineSimulator");
        VoleMachineSimulator->resize(800, 600);
        centralwidget = new QWidget(VoleMachineSimulator);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 480, 231, 61));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        addInstructionButton = new QPushButton(widget);
        addInstructionButton->setObjectName("addInstructionButton");

        horizontalLayout->addWidget(addInstructionButton);

        clearMemoryButton = new QPushButton(widget);
        clearMemoryButton->setObjectName("clearMemoryButton");

        horizontalLayout->addWidget(clearMemoryButton);

        Exit = new QPushButton(centralwidget);
        Exit->setObjectName("Exit");
        Exit->setGeometry(QRect(660, 500, 100, 29));
        Exit->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4CAF50;      /* Green color /\n"
"    color: white;                   / Text color /\n"
"    border: none;                   / No border /\n"
"    padding: 10px 20px;             / Padding /\n"
"    border-radius: 5px;             / Rounded corners /\n"
"    font-size: 16px;                / Font size /\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #45a049;      / Darker green on hover /\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e8e41;      / Even darker green when pressed */\n"
"}"));
        decodeMessage = new QTextEdit(centralwidget);
        decodeMessage->setObjectName("decodeMessage");
        decodeMessage->setGeometry(QRect(490, 240, 281, 71));
        decodeMessage->setReadOnly(true);
        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(290, 40, 141, 331));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        RegistersLabel = new QLabel(widget1);
        RegistersLabel->setObjectName("RegistersLabel");

        verticalLayout_3->addWidget(RegistersLabel);

        registersList = new QListWidget(widget1);
        registersList->setObjectName("registersList");

        verticalLayout_3->addWidget(registersList);

        clearRegistersButton = new QPushButton(widget1);
        clearRegistersButton->setObjectName("clearRegistersButton");

        verticalLayout_3->addWidget(clearRegistersButton);

        widget2 = new QWidget(centralwidget);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(561, 50, 201, 171));
        verticalLayout_2 = new QVBoxLayout(widget2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        PC_Label = new QLabel(widget2);
        PC_Label->setObjectName("PC_Label");

        verticalLayout_2->addWidget(PC_Label);

        pcVeiwBox = new QLineEdit(widget2);
        pcVeiwBox->setObjectName("pcVeiwBox");

        verticalLayout_2->addWidget(pcVeiwBox);

        fetchButton = new QPushButton(widget2);
        fetchButton->setObjectName("fetchButton");

        verticalLayout_2->addWidget(fetchButton);

        decodeButton = new QPushButton(widget2);
        decodeButton->setObjectName("decodeButton");

        verticalLayout_2->addWidget(decodeButton);

        executeButton = new QPushButton(widget2);
        executeButton->setObjectName("executeButton");

        verticalLayout_2->addWidget(executeButton);

        widget3 = new QWidget(centralwidget);
        widget3->setObjectName("widget3");
        widget3->setGeometry(QRect(30, 40, 231, 441));
        verticalLayout = new QVBoxLayout(widget3);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        MainMemoryLabel = new QLabel(widget3);
        MainMemoryLabel->setObjectName("MainMemoryLabel");

        verticalLayout->addWidget(MainMemoryLabel);

        memoryList = new QListWidget(widget3);
        memoryList->setObjectName("memoryList");
        memoryList->setProperty("isWrapping", QVariant(false));
        memoryList->setResizeMode(QListView::ResizeMode::Fixed);
        memoryList->setSortingEnabled(false);

        verticalLayout->addWidget(memoryList);

        addInstructionLabel = new QLabel(widget3);
        addInstructionLabel->setObjectName("addInstructionLabel");

        verticalLayout->addWidget(addInstructionLabel);

        addInstructionBox = new QLineEdit(widget3);
        addInstructionBox->setObjectName("addInstructionBox");

        verticalLayout->addWidget(addInstructionBox);

        widget4 = new QWidget(centralwidget);
        widget4->setObjectName("widget4");
        widget4->setGeometry(QRect(290, 390, 271, 131));
        verticalLayout_4 = new QVBoxLayout(widget4);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget4);
        label->setObjectName("label");

        verticalLayout_4->addWidget(label);

        screenBox = new QTextEdit(widget4);
        screenBox->setObjectName("screenBox");
        screenBox->setReadOnly(true);

        verticalLayout_4->addWidget(screenBox);

        VoleMachineSimulator->setCentralWidget(centralwidget);
        menubar = new QMenuBar(VoleMachineSimulator);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menua = new QMenu(menubar);
        menua->setObjectName("menua");
        VoleMachineSimulator->setMenuBar(menubar);
        statusbar = new QStatusBar(VoleMachineSimulator);
        statusbar->setObjectName("statusbar");
        VoleMachineSimulator->setStatusBar(statusbar);

        menubar->addAction(menua->menuAction());

        retranslateUi(VoleMachineSimulator);
        QObject::connect(Exit, &QPushButton::clicked, VoleMachineSimulator, qOverload<>(&QMainWindow::close));

        memoryList->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(VoleMachineSimulator);
    } // setupUi

    void retranslateUi(QMainWindow *VoleMachineSimulator)
    {
        VoleMachineSimulator->setWindowTitle(QCoreApplication::translate("VoleMachineSimulator", "MainWindow", nullptr));
        addInstructionButton->setText(QCoreApplication::translate("VoleMachineSimulator", "Add Instruction", nullptr));
        clearMemoryButton->setText(QCoreApplication::translate("VoleMachineSimulator", "Clear Memory", nullptr));
        Exit->setText(QCoreApplication::translate("VoleMachineSimulator", "Exit", nullptr));
        decodeMessage->setPlaceholderText(QCoreApplication::translate("VoleMachineSimulator", "Decoding Message", nullptr));
        RegistersLabel->setText(QCoreApplication::translate("VoleMachineSimulator", "Registers", nullptr));
        clearRegistersButton->setText(QCoreApplication::translate("VoleMachineSimulator", "Clear Registers", nullptr));
        PC_Label->setText(QCoreApplication::translate("VoleMachineSimulator", "Program Counter", nullptr));
        fetchButton->setText(QCoreApplication::translate("VoleMachineSimulator", "fetch", nullptr));
        decodeButton->setText(QCoreApplication::translate("VoleMachineSimulator", "decode", nullptr));
        executeButton->setText(QCoreApplication::translate("VoleMachineSimulator", "execute", nullptr));
        MainMemoryLabel->setText(QCoreApplication::translate("VoleMachineSimulator", "Main Memory", nullptr));
        addInstructionLabel->setText(QCoreApplication::translate("VoleMachineSimulator", "Add Instruction", nullptr));
        label->setText(QCoreApplication::translate("VoleMachineSimulator", "Screen", nullptr));
        menua->setTitle(QCoreApplication::translate("VoleMachineSimulator", "Vole Machine Simulator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VoleMachineSimulator: public Ui_VoleMachineSimulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
