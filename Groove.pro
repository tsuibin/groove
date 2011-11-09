#-------------------------------------------------
#
# Project created by QtCreator 2011-11-08T09:18:11
#
#-------------------------------------------------

QT       += core gui network sql

TARGET = Groove
TEMPLATE = app


SOURCES += main.cpp\
        comm.cpp \
    sendmessage.cpp \
    workspace.cpp \
    tip.cpp \
    message.cpp \
    ipinfo.cpp \
    iplist.cpp \
    commserver.cpp \
    login.cpp \
    gsession.cpp

HEADERS  += comm.h \
    sendmessage.h \
    workspace.h \
    tip.h \
    message.h \
    ipinfo.h \
    iplist.h \
    commserver.h \
    login.h \
    gsession.h

FORMS    += comm.ui \
    sendmessage.ui \
    workspace.ui \
    tip.ui \
    message.ui \
    login.ui
