QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Specify the paths to include your headers and sources
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/src
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/CPU.cpp \
    src/Machine.cpp \
    src/Memory.cpp \
    src/CU.cpp \
    src/ALU.cpp \
    src/Register.cpp

HEADERS += \
    mainwindow.h \
    include/CPU.h \
    include/Machine.h \
    include/Memory.h \
    include/CU.h \
    include/ALU.h \
    include/Register.h

FORMS += \
    mainwindow.ui

# Deployment rules (optional)
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imgs.qrc
