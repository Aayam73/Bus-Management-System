QT += quick quickcontrols2 sql
QT += core gui widgets sql printsupport
QT += core gui widgets sql printsupport


CONFIG += c++17

SOURCES += \
    main.cpp \
    reservationhandler.cpp \
    qrcodegen.cpp

HEADERS += \
    reservationhandler.h \
    qrcodegen.hpp


RESOURCES += qml.qrc

QMAKE_EXTRA_COMPILERS -= qrc


