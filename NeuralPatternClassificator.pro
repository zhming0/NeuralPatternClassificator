#-------------------------------------------------
#
# Project created by QtCreator 2012-07-06T14:21:20
#
#-------------------------------------------------

QT       += core xml

QT       -= gui

TARGET = NeuralPatternClassificator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    neuralnetwork.cpp \
    neuron.cpp \
    gradient.cpp \
    neurallayer.cpp \
    neuralnetworkxmlhandler.cpp

HEADERS += \
    neuralnetwork.h \
    neuron.h \
    gradient.h \
    neurallayer.h \
    neuralnetworkxmlhandler.h
