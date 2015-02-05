#-------------------------------------------------
#
# Project created by QtCreator 2015-01-14T09:44:05
#
#-------------------------------------------------

QT       += core gui dbus widgets multimedia multimediawidgets

CONFIG += qt debug c++11

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
    src/ui/base/faderwidget.h \
    src/ui/onekeycheck/onekeycheckwidget.h \
    src/ui/onekeycheck/tabbutton.h \
    src/ui/onekeycheck/mydelegate.h \
    src/util/modelutil.h \
    src/common/globals.h \
    src/ui/base/taskscene.h \
    src/state/common/checktask.h \
    src/state/common/checktaskgroup.h \
    src/ui/common/taskbutton.h \
    src/ui/detailreport/deviceconnectrpt.h \
    src/ui/detailreport/systemsecurityrpt.h \
    src/ui/detailreport/netrecordrpt.h \
    src/ui/detailreport/basicinforpt.h \
    src/ui/detailreport/basereport.h

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
    src/ui/common/sysbuttongroup.cpp \
    src/ui/base/opacitywidget.cpp \
    src/ui/base/faderwidget.cpp \
    src/ui/onekeycheck/onekeycheckwidget.cpp \
    src/main.cpp \
    src/ui/onekeycheck/tabbutton.cpp \
    src/ui/onekeycheck/mydelegate.cpp \
    src/util/modelutil.cpp \
    src/common/globals.cpp \
    src/ui/base/taskscene.cpp \
    src/state/common/checktask.cpp \
    src/state/common/checktaskgroup.cpp \
    src/ui/common/taskbutton.cpp \
    src/ui/detailreport/deviceconnectrpt.cpp \
    src/ui/detailreport/systemsecurityrpt.cpp \
    src/ui/detailreport/netrecordrpt.cpp \
    src/ui/detailreport/basicinforpt.cpp \
    src/ui/detailreport/basereport.cpp

copyotherfile.commands = $(COPY_DIR) $$PWD/otherfile $$OUT_PWD
first.depends = $(first) copyotherfile
export(first.depends)
export(copyotherfile.commands)
QMAKE_EXTRA_TARGETS += first copyotherfile
