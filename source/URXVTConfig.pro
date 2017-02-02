#-------------------------------------------------
#
# Project created by QtCreator 2017-01-22T02:26:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = urxvtconfig
TEMPLATE = app


SOURCES += main.cpp\
        urxvtconfig.cpp

HEADERS  += urxvtconfig.h

FORMS    += urxvtconfig.ui

shortcut.path = /usr/share/applications
shortcut.files = urxvtconfig.desktop
target.path = /usr/bin

INSTALLS += target shortcut

