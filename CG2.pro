#-------------------------------------------------
#
# Project created by QtCreator 2019-04-13T23:09:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        affine.cpp \
        circle.cpp \
        circleinfo.cpp \
        item.cpp \
        line.cpp \
        lineinfo.cpp \
        main.cpp \
        rectangle.cpp \
        rectinfo.cpp \
        scene.cpp \
        window.cpp

HEADERS += \
        affine.h \
        circle.h \
        circleinfo.h \
        item.h \
        line.h \
        lineinfo.h \
        rectangle.h \
        rectinfo.h \
        scene.h \
        window.h

FORMS += \
        circleinfo.ui \
        lineinfo.ui \
        rectinfo.ui \
        window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
