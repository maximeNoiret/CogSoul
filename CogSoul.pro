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
        types.cpp \
        ptt_functions.cpp \
        ptt_main.cpp

HEADERS += \
    entityController.h \
    mapManagement.h \
    settingsManagement.h \
    terminalManagement.h \
    types.h \
    ptt_functions.h \
    ptt_main.h
