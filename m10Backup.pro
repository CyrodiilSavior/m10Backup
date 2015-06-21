#-------------------------------------------------
#
# m10 Backup
#An Open Source Backup Solution
#
# Project created by Garrett Adams in QtCreator 2015-04-10T17:36:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = m10Backup
TEMPLATE = app

#Set Vars
QUAZIPCODEDIR = "/home/garrett/Desktop/ZipStuff/quazip-0.7.1/quazip"
ZLIBCODEDIR = "/home/garrett/Desktop/ZipStuff/Libs"

unix{
    LIBS += -L$${ZLIBCODEDIR} -lz
}

SOURCES += main.cpp\
        mainwindow.cpp \
    quaziputil.cpp \
    threadmanager.cpp \
    schedulechecker.cpp \
    progressthread.cpp \
    newbackup.cpp
INCLUDEPATH += $${QUAZIPCODEDIR}
HEADERS += $${QUAZIPCODEDIR}/*.h \
    quaziputil.h \
    threadmanager.h \
    schedulechecker.h \
    progressthread.h \
    newbackup.h
SOURCES += $${QUAZIPCODEDIR}/*.cpp
SOURCES += $${QUAZIPCODEDIR}/*.c
HEADERS  += mainwindow.h

FORMS    += mainwindow.ui \
    newbackup.ui

OTHER_FILES += \
    counter.txt
