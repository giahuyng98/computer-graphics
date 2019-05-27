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

# You can also make your code fail to compile  if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        affine.cpp \
        apidrawer.cpp \
        circle.cpp \
        circleinfo.cpp \
        cube.cpp \
        cylinder.cpp \
        ellipse.cpp \
        ellipseinfo.cpp \
        frameparser.cpp \
        item.cpp \
        line.cpp \
        lineinfo.cpp \
        main.cpp \
        rectangle.cpp \
        rectinfo.cpp \
        scene.cpp \
        scene2d.cpp \
        scene3d.cpp \
        sceneanimation.cpp \
        sphere.cpp \
        window.cpp

HEADERS += \
        affine.h \
        apidrawer.h \
        circle.h \
        circleinfo.h \
        cube.h \
        cylinder.h \
        ellipse.h \
        ellipseinfo.h \
        frameparser.h \
        item.h \
        line.h \
        lineinfo.h \
        rectangle.h \
        rectinfo.h \
        scene.h \
        scene2d.h \
        scene3d.h \
        sceneanimation.h \
        sphere.h \
        window.h

FORMS += \
        circleinfo.ui \
        ellipseinfo.ui \
        lineinfo.ui \
        rectinfo.ui \
        window.ui

QMAKE_CFLAGS_DEBUG += \
                -Wall \
                -Wextra\
                -pedantic\
                 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    myicon.qrc

DISTFILES +=
