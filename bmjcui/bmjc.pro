#-------------------------------------------------
#
# Project created by QtCreator 2015-01-14T09:44:05
#
#-------------------------------------------------

QT       += core gui printsupport dbus widgets multimedia multimediawidgets

CONFIG += qt debug c++11

TARGET = bmjc
TEMPLATE = app

#DBUS_ADAPTORS += src/state/onekeycheck.xml
#DBUS_INTERFACES += src/state/onekeycheck.xml



RESOURCES += \
    resource/bmjc.qrc

HEADERS += \
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
    src/ui/commoncheck/tabbutton.h \
    src/ui/commoncheck/mydelegate.h \
    src/util/modelutil.h \
    src/common/globals.h \
    src/state/common/checktask.h \
    src/state/common/checktaskgroup.h \
    src/ui/common/taskbutton.h \
    src/ui/detailreport/deviceconnectrpt.h \
    src/ui/detailreport/systemsecurityrpt.h \
    src/ui/detailreport/basicinforpt.h \
    src/ui/detailreport/basereport.h \
    src/ui/detailreport/netrecordcommonrpt.h \
    src/ui/detailreport/securitythreatrpt.h \
    src/ui/detailreport/usbrecordcommonrpt.h \
    src/ui/filecheck/filecheckwidget.h \
    src/state/filecheckstate.h \
    src/state/trojancheckstate.h \
    src/ui/detailreport/filecheckcommonrpt.h \
    src/ui/detailreport/trojancheckrpt.h \
    src/ui/trojancheck/trojancheckwidget.h \
    src/state/imagecheckstate.h \
    src/state/usbdeepcheckstate.h \
    src/state/netrecorddeepcheckstate.h \
    src/ui/detailreport/imagecheckrpt.h \
    src/ui/detailreport/netrecorddeeprpt.h \
    src/ui/detailreport/usbrecorddeeprpt.h \
    src/ui/detailreport/usbrecordallrpt.h \
    src/ui/detailreport/netrecordallrpt.h \
    src/ui/imagecheck/imagecheckwidget.h \
    src/ui/deepcheck/usbdeepcheckwidget.h \
    src/ui/deepcheck/netrecorddeepcheckwidget.h \
    src/ui/checkreport/checkreportwidget.h \
    src/util/rptcreator.h \
    src/state/commoncheckstate.h \
    src/ui/commoncheck/commoncheckwidget.h \
    src/ui/deepcheck/deepcheckwidget.h \
    src/state/onekeycheckstate.h \
    src/ui/onekeycheck/onekeycheckmainwidget.h \
    src/ui/onekeycheck/onekeychecksettingwidget.h \
    src/ui/onekeycheck/filechecksettingpart.h \
    src/ui/onekeycheck/imagechecksettingpart.h \
    src/ui/onekeycheck/trojanchecksettingpart.h \
    src/ui/onekeycheck/commonchecksettingpart.h \
    src/ui/onekeycheck/checkbutton.h

SOURCES += \
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
    src/main.cpp \
    src/ui/commoncheck/tabbutton.cpp \
    src/ui/commoncheck/mydelegate.cpp \
    src/util/modelutil.cpp \
    src/common/globals.cpp \
    src/state/common/checktask.cpp \
    src/state/common/checktaskgroup.cpp \
    src/ui/common/taskbutton.cpp \
    src/ui/detailreport/deviceconnectrpt.cpp \
    src/ui/detailreport/systemsecurityrpt.cpp \
    src/ui/detailreport/basicinforpt.cpp \
    src/ui/detailreport/basereport.cpp \
    src/ui/detailreport/netrecordcommonrpt.cpp \
    src/ui/detailreport/securitythreatrpt.cpp \
    src/ui/detailreport/usbrecordcommonrpt.cpp \
    src/ui/filecheck/filecheckwidget.cpp \
    src/state/filecheckstate.cpp \
    src/state/trojancheckstate.cpp \
    src/ui/detailreport/filecheckcommonrpt.cpp \
    src/ui/detailreport/trojancheckrpt.cpp \
    src/ui/trojancheck/trojancheckwidget.cpp \
    src/state/imagecheckstate.cpp \
    src/state/usbdeepcheckstate.cpp \
    src/state/netrecorddeepcheckstate.cpp \
    src/ui/detailreport/imagecheckrpt.cpp \
    src/ui/detailreport/netrecorddeeprpt.cpp \
    src/ui/detailreport/usbrecorddeeprpt.cpp \
    src/ui/detailreport/usbrecordallrpt.cpp \
    src/ui/detailreport/netrecordallrpt.cpp \
    src/ui/imagecheck/imagecheckwidget.cpp \
    src/ui/deepcheck/usbdeepcheckwidget.cpp \
    src/ui/deepcheck/netrecorddeepcheckwidget.cpp \
    src/ui/checkreport/checkreportwidget.cpp \
    src/util/rptcreator.cpp \
    src/state/commoncheckstate.cpp \
    src/ui/commoncheck/commoncheckwidget.cpp \
    src/ui/deepcheck/deepcheckwidget.cpp \
    src/state/onekeycheckstate.cpp \
    src/ui/onekeycheck/onekeycheckmainwidget.cpp \
    src/ui/onekeycheck/onekeychecksettingwidget.cpp \
    src/ui/onekeycheck/filechecksettingpart.cpp \
    src/ui/onekeycheck/imagechecksettingpart.cpp \
    src/ui/onekeycheck/trojanchecksettingpart.cpp \
    src/ui/onekeycheck/commonchecksettingpart.cpp \
    src/ui/onekeycheck/checkbutton.cpp

copyotherfile.commands = $(COPY_DIR) $$PWD/otherfile $$OUT_PWD
first.depends = $(first) 
export(first.depends)
export(copyotherfile.commands)
QMAKE_EXTRA_TARGETS += first copyotherfile
