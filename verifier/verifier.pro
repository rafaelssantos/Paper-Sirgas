TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    point.cpp \
    pointmanager.cpp \
    datetime.cpp \
    inspector.cpp

HEADERS += \
    point.h \
    pointmanager.h \
    datetime.h \
    inspector.h
