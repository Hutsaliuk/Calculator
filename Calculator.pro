# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = Calculator
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS = \
   $$PWD/Calculator/Calculation.h \
   $$PWD/Calculator/Checks.h \
   $$PWD/Calculator/ErrorProcessing.h \
   $$PWD/Calculator/resource.h

SOURCES = \
   $$PWD/Calculator/Calculation.cpp \
   $$PWD/Calculator/Checks.cpp \
   $$PWD/Calculator/ErrorProcessing.cpp \
   $$PWD/Calculator/main.cpp

INCLUDEPATH = \
    $$PWD/Calculator

#DEFINES = 

