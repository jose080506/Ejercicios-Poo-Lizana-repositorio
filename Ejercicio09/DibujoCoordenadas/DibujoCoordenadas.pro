QT += widgets sql

CONFIG += c++17

SOURCES += main.cpp \
           admindb.cpp \
           login.cpp \
           pintura.cpp \
           mainwindow.cpp

HEADERS += admindb.h \
           login.h \
           pintura.h \
           mainwindow.h

FORMS   += login.ui
