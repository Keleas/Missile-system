TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        testmodel.cpp

HEADERS += \
    abstractmodel.h \
    any_channel.h \
    channel_crrier.h \
    msg_channel.h \
    testmodelb.h
