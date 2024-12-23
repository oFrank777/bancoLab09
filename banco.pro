QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    account.cpp \
    accountmanager.cpp \
    client.cpp \
    main.cpp \
    mainwindow.cpp \
    transaction.cpp \

HEADERS += \
    account.h \
    account.h \
    accountmanager.h \
    client.h \
    mainwindow.h \
    transaction.h \

FORMS += \
    mainwindow.ui
