QT += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WaveControlApp
TEMPLATE = app

SOURCES += main.cpp \
           wavecontrolwindow.cpp

HEADERS += wavecontrolwindow.h
