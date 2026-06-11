#-------------------------------------------------
#
# Ejercicio 03 - Lienzo colaborativo en tiempo real
# POO 2026 - Cenci / Gandini / Lizana
#
#-------------------------------------------------

QT += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET   = Ejercicio03
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp       \
    Ventana.cpp    \
    Lienzo.cpp     \
    ModeloDibujo.cpp \
    Sincronizador.cpp

HEADERS += \
    Ventana.h      \
    Lienzo.h       \
    ModeloDibujo.h \
    Sincronizador.h
