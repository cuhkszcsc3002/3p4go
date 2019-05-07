#-------------------------------------------------
#
# Project created by QtCreator 2019-04-10T18:54:37
#
#-------------------------------------------------

QT += core gui
QT += network

CONFIG += c++11 console
CONFIG += sdk_no_version_check

# GMP
#INCLUDEPATH += C:/gmpbuild/include

#DEPENDPATH += C:/gmpbuild/include

#LIBS += -LC:/gmpbuild/lib/ -lgmpxx -lgmp

LIBS += -lgmpxx -lgmp


INCLUDEPATH += /usr/local/Cellar/gmp/6.1.2_2/include

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3P4Go
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

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    game.cpp \
    client.cpp \
    ip.cpp \
    move.cpp \
    movechain.cpp \
    rsa2.cpp \
    key2.cpp \
    coordinate.cpp \
    server.cpp

HEADERS += \
    mainwindow.h \
    client.h \
    game.h \
    ip.h \
    move.h \
    movechain.h \
    rsa2.h \
    key2.h \
    coordinate.h \
    server.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(QtWebApp/httpserver/httpserver.pri)
OTHER_FILES += webapp1.ini

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2/lib/release/ -lgmpxx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2/lib/debug/ -lgmpxx
else:unix: LIBS += -L$$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2/lib/ -lgmpxx

INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2
DEPENDPATH += $$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2/lib/release/libgmpxx.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2/lib/debug/libgmpxx.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2/lib/release/gmpxx.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2/lib/debug/gmpxx.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2/lib/libgmpxx.a
