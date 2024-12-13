TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        mapManagement.cpp \
        terminalManagement.cpp

INCLUDEPATH += /usr/include/c++/11/

HEADERS += \
    mapManagement.h \
    terminalManagement.h \
    types.h
