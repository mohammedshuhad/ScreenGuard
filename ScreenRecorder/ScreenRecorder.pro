TEMPLATE = app
TARGET = screen_recorder_app

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    screenrecorder.cpp

HEADERS += \
    screenrecorder.h
