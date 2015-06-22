#-------------------------------------------------
#
# m10 Backup
#An Open Source Backup Solution
#
# Project created by Garrett Adams in QtCreator 2015-04-10T17:36:12
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = m10Backup
TEMPLATE = app

#Set Vars

macx {
    QUAZIPCODEDIR_MAC = "/Users/garrett/Desktop/ZipStuff/quazip-0.7.1/quazip"
    ZLIBCODEDIR_MAC = "/Users/garrett/Desktop/ZipStuff/Libs"
}

unix:!macx{
    QUAZIPCODEDIR_LINUX = "/home/garrett/Desktop/ZipStuff/quazip-0.7.1/quazip"
    ZLIBCODEDIR_LINUX = "/home/garrett/Desktop/ZipStuff/Libs"
}




    LIBS += -L$${ZLIBCODEDIR} -lz


SOURCES += main.cpp\
        mainwindow.cpp \
    quaziputil.cpp \
    threadmanager.cpp \
    schedulechecker.cpp \
    progressthread.cpp \
    newbackup.cpp \
    databasemanager.cpp
INCLUDEPATH += $${QUAZIPCODEDIR}
HEADERS += $${QUAZIPCODEDIR}/*.h \
    quaziputil.h \
    threadmanager.h \
    schedulechecker.h \
    progressthread.h \
    newbackup.h \
    databasemanager.h
SOURCES += $${QUAZIPCODEDIR}/*.cpp
SOURCES += $${QUAZIPCODEDIR}/*.c
HEADERS  += mainwindow.h

FORMS    += mainwindow.ui \
    newbackup.ui

OTHER_FILES += \
    counter.txt
