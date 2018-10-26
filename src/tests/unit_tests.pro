include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
    lvm_wt_tests.h \
    bin_map_stream_reader_tests.h

SOURCES += \
        main.cpp

INCLUDEPATH += \
    $$PWD/..

LIBS += -L$$PWD/../../build
LIBS += -ltdd_kata_bin_mapping