QT += network

win32 {
QMAKE_LFLAGS += -static-libgcc
}

SOURCES += \
    main.cpp \
    QWsServer.cpp \
    QWsSocket.cpp \
    Server.cpp \
    mainwindow.cpp

HEADERS += \
    QWsServer.h \
    QWsSocket.h \
    Server.h \
    mainwindow.h
