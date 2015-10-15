#-------------------------------------------------
#
# Project created by QtCreator 2015-05-07T16:42:51
#
#-------------------------------------------------
#CONFIG += release
CONFIG += C++11

QMAKE_CXXFLAGS+= -openmp

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LF_Toolbox
TEMPLATE = app

SOURCES += src/main.cpp \
           src/gui_signals.cpp \
           src/gui_slots.cpp \
        src/gui_toolbox.cpp

HEADERS += \
    include/gui_toolbox.h


RC_ICONS += resources/icon.ico

FORMS    += ui_forms/gui_windows.ui
RESOURCES += \
    resources/recources.qrc

OTHER_FILES +=
