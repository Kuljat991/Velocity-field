QT += core
QT += gui

TARGET = Polje_brzina
CONFIG += console
CONFIG -= app_bundle
INCLUDEPATH += D:/boost/boost_1_60_0/
LIBS += "-LC:/boost/boost_1_60_0/stage/lib/"

TEMPLATE = app

SOURCES += main.cpp

