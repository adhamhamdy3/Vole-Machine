#include "VoleMachine_UI.h"
#include<QIcon>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Hello World\n";
    a.setWindowIcon(QIcon(":/images/vole-machine.ico"));
    MainWindow w;
    w.show();
    return a.exec();
}
