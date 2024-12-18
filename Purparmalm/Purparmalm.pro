TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        entityController.cpp \
        main.cpp \
        mapManagement.cpp \
        terminalManagement.cpp

HEADERS += \
    entityController.h \
    mapManagement.h \
    terminalManagement.h \
    types.h
