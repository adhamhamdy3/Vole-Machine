QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += $$PWD/src
SOURCES += \
    VoleMachine_UI.cpp \
    main.cpp \
    src/CPU.cpp \
    src/Machine.cpp \
    src/Memory.cpp \
    src/CU.cpp \
    src/ALU.cpp \
    src/Register.cpp \
    src/Utilities.cpp

HEADERS += \
    VoleMachine_UI.h \
    src/CPU.h \
    src/Machine.h \
    src/Memory.h \
    src/CU.h \
    src/ALU.h \
    src/Register.h \
    src/Utilities.h

FORMS += \
    VoleMachine_UI.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    volemachine.rc

