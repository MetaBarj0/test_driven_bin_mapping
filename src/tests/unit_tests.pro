include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
    lvm_wt_tests.h

SOURCES += \
        main.cpp

INCLUDEPATH += \
    $$PWD/..

LIBS += -L$$PWD/../../build
LIBS += -ltdd_kata_bin_mapping