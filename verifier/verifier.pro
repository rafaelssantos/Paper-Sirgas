TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    point.cpp \
    pointmanager.cpp \
    datetime.cpp \
    inspector.cpp \
    settings.cpp

HEADERS += \
    point.h \
    pointmanager.h \
    datetime.h \
    inspector.h \
    settings.h \
    errorcode.h
