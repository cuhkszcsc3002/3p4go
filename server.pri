
HEADERS += server.h \
    requestmapper.h \
    $$PWD/receiveforsigcontroller.h \
    $$PWD/receiveinvitecontroller.h \
    $$PWD/receiveplayerinfocontroller.h \
    $$PWD/receivenewmovecontroller.h




SOURCES += server.cpp \
    requestmapper.cpp \
    $$PWD/receiveforsigcontroller.cpp \
    $$PWD/receiveplayerinfocontroller.cpp \
    $$PWD/receiveinvitecontroller.cpp \
    $$PWD/receivenewmovecontroller.cpp

OTHER_FILES += $$PWD/webapp1.ini
