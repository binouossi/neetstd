TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
#    fonction.cpp

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += /usr/include/
#LIBS += -L/usr/lib
LIBS += -L/usr/lib/x86_64-linux-gnu/
#LIBS += -lgssapi
#LIBS += -Wl
LIBS += -lgss
#LIBS += -relro
LIBS += -lgssrpc
LIBS += -lgssapi_krb5
#LIBS += -lkrb5
#LIBS += -lk5crypto
#LIBS += -lcom_err
#LIBS += pkg-config gss --cflags --libs

HEADERS += \
    func.h
