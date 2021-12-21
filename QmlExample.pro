#-------------------------------------------------
#
# Copyright (C) 2003-2103 CamelSoft Corporation
#
#-------------------------------------------------

QT += qml quick widgets svg

CONFIG += c++11

SOURCES += main.cpp \
    imageitem.cpp \
    qmlhelper.cpp \
    mmainwindow.cpp \
    tablemodel.cpp \
    titlebar.cpp \
    widgets/delegate/delegate.cpp \
    widgets/model/iconitemmodel.cpp \
    widgets/arrowcirclebutton.cpp \
    widgets/textdocument.cpp \
    widgets/utils.cpp \
    widgets/model/treemodel.cpp \
    widgets/model/treeitem.cpp \
    screenshotitem.cpp \
    core/viewprovider.cpp \
    widgets/blindswidget.cpp \
    widgets/pieimagedisplay.cpp

RESOURCES += qml.qrc

HEADERS += \
    imageitem.h \
    qmlhelper.h \
    mmainwindow.h \
    tablemodel.h \
    titlebar.h \
    widgets/delegate/delegate.h \
    widgets/model/tablemodeltemplate.h \
    widgets/model/iconitemmodel.h \
    widgets/arrowcirclebutton.h \
    widgets/textdocument.h \
    widgets/utils.h \
    widgets/model/treemodel.h \
    widgets/model/treeitem.h \
    screenshotitem.h \
    core/viewprovider.h \
    widgets/blindswidget.h \
    widgets/pieimagedisplay.h

DISTFILES +=
