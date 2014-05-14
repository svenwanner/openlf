#-------------------------------------------------
#
# Project created by QtCreator 2014-04-23T15:07:06
#
#-------------------------------------------------

QT       += core gui \
            widgets \
            printsupport

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViewLF
TEMPLATE = app

CONFIG += debug_and_release
CONFIG += c++11

macx {
QMAKE_CXXFLAGS += -stdlib=libc++
QMAKE_CXXFLAGS += -mmacosx-version-min=10.7
}

SOURCES += main.cpp \
           LF_viewer.cpp \
           LF_viewer_signals.cpp \
           LF_viewer_slots.cpp \
           LF_dockWidgets.cpp \
           LF_viewer_child.cpp
linux-g++ {
LIBS  = -L./../../build/lib
LIBS += -L/usr/lib/X86_64-linux-gnu
}
macx {
LIBS += -L./../ 
LIBS += -L/opt/local/lib
}
LIBS += -L/usr/local/lib
LIBS += -llibopenlf

LIBS += -lhdf5
LIBS += -lhdf5_cpp
LIBS += -lhdf5_hl
LIBS += -lhdf5_hl_cpp

LIBS += -lboost_iostreams
LIBS += -lboost_context
LIBS += -lboost_filesystem
LIBS += -lboost_system

LIBS += -lvigraimpex

HEADERS  += LF_viewer.h \
            LF_viewer_child.h

INCLUDEPATH += ./../../includes \
				/usr/local/include/


FORMS    += \
    MainWindow.ui

RESOURCES += \
    recources.qrc
