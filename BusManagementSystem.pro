QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += core gui sql
CONFIG += console


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountwindow.cpp \
    database.cpp \
    homewindow.cpp \
    main.cpp \
    loginwindow.cpp \
    signupwindow.cpp \
    startwindow.cpp

HEADERS += \
    accountwindow.h \
    database.h \
    homewindow.h \
    loginwindow.h \
    signupwindow.h \
    startwindow.h \

FORMS += \
    accountwindow.ui \
    homewindow.ui \
    loginwindow.ui \
    signupwindow.ui \
    startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
