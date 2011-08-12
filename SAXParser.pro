#-------------------------------------------------
#
# Project created by QtCreator 2011-08-05T14:32:42
#
#-------------------------------------------------

QT       += core xml

QT       -= gui

TARGET = SAXParser
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    kmlreader.cpp \
    gpxreader.cpp \
    trackparser.cpp

HEADERS += \
    kmlreader.h \
    cpoint.h \
    gpxreader.h \
    trackparser.h
