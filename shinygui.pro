#-------------------------------------------------
#
# Project created by QtCreator 2020-05-13T22:06:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = TolinoGUI
TEMPLATE = app


SOURCES += main.cpp\
        epdcontrol.cpp \
        mainwindow.cpp \
        settingsprovider.cpp \
        updater.cpp \
        weatherprovider.cpp

HEADERS  += mainwindow.h \
    epdcontrol.h \
    settingsprovider.h \
    updater.h \
    weatherprovider.h

FORMS    += mainwindow.ui \
    updater.ui
