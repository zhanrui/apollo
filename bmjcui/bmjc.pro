#-------------------------------------------------
#
# Project created by QtCreator 2015-01-14T09:44:05
#
#-------------------------------------------------

QT       += core gui dbus widgets multimedia multimediawidgets

CONFIG += qt debug

TARGET = bmjc
TEMPLATE = app

#DBUS_ADAPTORS += src/state/onekeycheck.xml
#DBUS_INTERFACES += src/state/onekeycheck.xml



RESOURCES += \
    resource/bmjc.qrc

HEADERS += \
    src/state/onekeycheckstate.h \
    src/common/common.h \
    src/ui/base/basestylewidget.h \
    src/ui/base/commonwidget.h \
    src/ui/base/shadowwidget.h \
    src/ui/base/staticbutton.h \
    src/ui/main/maintitlewidget.h \
    src/ui/main/mainwidget.h \
    src/ui/main/mainwindow.h \
    src/util/interfacefortool.h \
    src/util/toolutil.h \
    src/ui/common/sysbuttongroup.h \
    src/ui/base/opacitywidget.h \
    src/ui/base/faderwidget.h

SOURCES += \
    src/state/onekeycheckstate.cpp \
    src/ui/base/basestylewidget.cpp \
    src/ui/base/commonwidget.cpp \
    src/ui/base/shadowwidget.cpp \
    src/ui/base/staticbutton.cpp \
    src/ui/main/maintitlewidget.cpp \
    src/ui/main/mainwidget.cpp \
    src/ui/main/mainwindow.cpp \
    src/util/interfacefortool.cpp \
    src/util/toolutil.cpp \
    src/main.cpp \
    src/ui/common/sysbuttongroup.cpp \
    src/ui/base/opacitywidget.cpp \
    src/ui/base/faderwidget.cpp
