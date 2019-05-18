
HEADERS += server.h \
    requestmapper.h \
    $$PWD/receiveforsigcontroller.h \
    $$PWD/receiveinvitecontroller.h \
    $$PWD/receiveplayerinfocontroller.h \
    $$PWD/receivenewmovecontroller.h \
    $$PWD/helloworldcontroller.h




SOURCES += server.cpp \
    requestmapper.cpp \
    $$PWD/receiveforsigcontroller.cpp \
    $$PWD/receiveplayerinfocontroller.cpp \
    $$PWD/receiveinvitecontroller.cpp \
    $$PWD/receivenewmovecontroller.cpp \
    $$PWD/helloworldcontroller.cpp

OTHER_FILES += $$PWD/webapp1.ini
