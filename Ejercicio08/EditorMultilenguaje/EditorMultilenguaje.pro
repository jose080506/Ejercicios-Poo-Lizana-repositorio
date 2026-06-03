QT += widgets

CONFIG += c++17

SOURCES += main.cpp \
           controlador.cpp \
           pantalla.cpp \
           login.cpp \
           editorprincipal.cpp \
           modobloqueado.cpp \
           validadorsintaxis.cpp \
           validadorcpp.cpp \
           validadorpython.cpp \
           validadorjava.cpp

HEADERS += controlador.h \
           pantalla.h \
           login.h \
           editorprincipal.h \
           modobloqueado.h \
           validadorsintaxis.h \
           validadorcpp.h \
           validadorpython.h \
           validadorjava.h

FORMS   += login.ui
