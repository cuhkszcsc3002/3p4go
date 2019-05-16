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

INCLUDEPATH += C:/gmpbuild/include

DEPENDPATH += C:/gmpbuild/include

LIBS += -LC:/gmpbuild/lib/ -lgmpxx -lgmp


unix {
    INCLUDEPATH -= C:/gmpbuild/include

    DEPENDPATH -= C:/gmpbuild/include

    LIBS -= -LC:/gmpbuild/lib/ -lgmpxx -lgmp

    LIBS += -L$$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2/lib/ -lgmpxx

    PRE_TARGETDEPS += $$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2/lib/libgmpxx.a

    INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2
    
    DEPENDPATH += $$PWD/../../../../usr/local/Cellar/gmp/6.1.2_2
}


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

SOURCES += \
    main.cpp \
    mainwindow.cpp 


HEADERS += \
    mainwindow.h 


#HEADERS += client.h

#SOURCES += client.cpp


#HEADERS += game.h

#SOURCES += game.cpp



#HEADERS += server.h \
#    helloworldcontroller.h \
#    listdatacontroller.h \
#    logincontroller.h \
#    requestmapper.h

#SOURCES += server.cpp \
#    helloworldcontroller.cpp \
#    listdatacontroller.cpp \
#    logincontroller.cpp \
#    requestmapper.cpp

#OTHER_FILES += webapp1.ini


#HEADERS += ip.h \
#    move.h \
#    movechain.h \
#    rsa2.h \
#    key2.h \
#    coordinate.h


#SOURCES += ip.cpp \
#    move.cpp \
#    movechain.cpp \
#    rsa2.cpp \
#    key2.cpp \
#    coordinate.cpp



FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(QtWebApp/httpserver/httpserver.pri)
include(client.pri)
include(server.pri)
include(game.pri)
include(baseClasses.pri)

