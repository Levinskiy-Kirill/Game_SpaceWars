#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T14:55:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpaceWars
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    menuScreen.cpp \
    gameScreen.cpp \
    gameWidget.cpp \
    wall.cpp \
    ship.cpp \
    bullet.cpp \
    enemy.cpp \
    shopScreen.cpp \
    helpScreen.cpp

HEADERS  += mainwindow.h \
    menuScreen.h \
    gameScreen.h \
    gameWidget.h \
    wall.h \
    ship.h \
    constants.h \
    bullet.h \
    enemy.h \
    shopScreen.h \
    helpScreen.h

RESOURCES += \
    images.qrc \
    settings.qrc
