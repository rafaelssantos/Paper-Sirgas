TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    point.cpp \
    datetime.cpp \
    settings.cpp \
    timedaemon.cpp \
    pointmanager.cpp

HEADERS += \
    point.h \
    pointmanager.h \
    datetime.h \
    settings.h \
    errorcode.h \
    timedaemon.h
