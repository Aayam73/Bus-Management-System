QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += core gui sql
CONFIG += console
QT += quick gui
QT += quickcontrols2
QT += core gui sql quick




# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountwindow.cpp \
    bookingwindow.cpp \
    homewindow.cpp \
    main.cpp \
    loginwindow.cpp \
    paymenthandler.cpp \
    reservationhandler.cpp \
    signupwindow.cpp \
    startwindow.cpp \
    qrcodegen.cpp


HEADERS += \
    accountwindow.h \
    bookingwindow.h \
    homewindow.h \
    loginwindow.h \
    paymenthandler.h \
    reservationhandler.h \
    signupwindow.h \
    startwindow.h \
    qrcodegen.hpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

