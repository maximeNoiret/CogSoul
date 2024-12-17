TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        mapManagement.cpp \
        playerController.cpp \
        terminalManagement.cpp

HEADERS += \
    mapManagement.h \
    playerController.h \
    terminalManagement.h \
    types.h
