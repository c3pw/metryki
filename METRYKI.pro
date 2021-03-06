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
    LibraryWindow/AddEditAttribForm.cpp \
    LibraryWindow/AddEditComponentForm.cpp \
    LibraryWindow/AddEditLocalityForm.cpp \
    AddEditDeviceForm.cpp \
    DeviceWindow/DeviceWindow.cpp

HEADERS  += MainWindow.h \
    ConfigWindow/ConfigWindow.h \
    AboutWindow/AboutWindow.h \
    LibraryWindow/LibraryWindow.h \
    LibraryWindow/AddEditTypeForm.h \
    LibraryWindow/AddEditAttribForm.h \
    LibraryWindow/AddEditComponentForm.h \
    LibraryWindow/AddEditLocalityForm.h \
    AddEditDeviceForm.h \
    DeviceWindow/DeviceWindow.h

FORMS    += MainWindow.ui \
    ConfigWindow/ConfigWindow.ui \
    AboutWindow/AboutWindow.ui \
    LibraryWindow/LibraryWindow.ui \
    LibraryWindow/AddEditTypeForm.ui \
    LibraryWindow/AddEditAttribForm.ui \
    LibraryWindow/AddEditComponentForm.ui \
    LibraryWindow/AddEditLocalityForm.ui \
    AddEditDeviceForm.ui \
    DeviceWindow/DeviceWindow.ui

RESOURCES += \
    resources.qrc
