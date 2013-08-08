#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T14:37:14
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = METRYKI
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ConfigWindow/ConfigWindow.cpp \
    AboutWindow/AboutWindow.cpp \
    LibraryWindow/LibraryWindow.cpp \
    LibraryWindow/AddEditTypeForm.cpp \
    LibraryWindow/AddEditAttribForm.cpp

HEADERS  += MainWindow.h \
    ConfigWindow/ConfigWindow.h \
    AboutWindow/AboutWindow.h \
    LibraryWindow/LibraryWindow.h \
    LibraryWindow/AddEditTypeForm.h \
    LibraryWindow/AddEditAttribForm.h

FORMS    += MainWindow.ui \
    ConfigWindow/ConfigWindow.ui \
    AboutWindow/AboutWindow.ui \
    LibraryWindow/LibraryWindow.ui \
    LibraryWindow/AddEditTypeForm.ui \
    LibraryWindow/AddEditAttribForm.ui

RESOURCES +=
