TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        entityController.cpp \
        main.cpp \
        mapManagement.cpp \
        settingsManagement.cpp \
        terminalManagement.cpp \
        types.cpp

HEADERS += \
    entityController.h \
    mapManagement.h \
    settingsManagement.h \
    terminalManagement.h \
    types.h
