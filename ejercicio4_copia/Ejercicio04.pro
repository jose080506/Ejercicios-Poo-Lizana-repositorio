QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = Ejercicio04
TEMPLATE = app

SOURCES += \
    main.cpp \
    apiclient.cpp \
    kanban.cpp \
    columnawidget.cpp \
    tarjetawidget.cpp

HEADERS += \
    apiclient.h \
    kanban.h \
    columnawidget.h \
    tarjetawidget.h
