#-------------------------------------------------
#
# Project created by QtCreator 2015-01-14T09:44:05
#
#-------------------------------------------------

QT       += core gui dbus widgets multimedia multimediawidgets

TARGET = bmjc
TEMPLATE = app

#DBUS_ADAPTORS += src/state/onekeycheck.xml
#DBUS_INTERFACES += src/state/onekeycheck.xml



RESOURCES += \
    resource/bmjc.qrc

HEADERS += \
    src/state/onekeycheckstate.h \
    src/ui/common/shadowwidget.h \
    src/ui/main/mainwidget.h \
    src/ui/main/mainwindow.h \
    src/util/interfacefortool.h \
    src/util/toolutil.h \
    src/ui/common/basestylewidget.h \
    src/ui/main/maintitlewidget.h \
    src/common/common.h \
    src/ui/common/commonwidget.h \
    src/ui/common/staticbutton.h

SOURCES += \
    src/state/onekeycheckstate.cpp \
    src/ui/common/shadowwidget.cpp \
    src/ui/main/mainwidget.cpp \
    src/ui/main/mainwindow.cpp \
    src/util/interfacefortool.cpp \
    src/util/toolutil.cpp \
    src/main.cpp \
    src/ui/common/basestylewidget.cpp \
    src/ui/main/maintitlewidget.cpp \
    src/ui/common/commonwidget.cpp \
    src/ui/common/staticbutton.cpp







