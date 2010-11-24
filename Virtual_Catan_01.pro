#-------------------------------------------------
#
# Project created by QtCreator 2010-11-01T18:44:32
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Virtual_Catan_01
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    catan.cpp \
    player.cpp \
    gameboard.cpp \
    timeFunc.cpp

HEADERS += \
    player.h \
    catan.h \
    gameboard.h \
    timeFunc.h

OTHER_FILES += \
    app.qml
