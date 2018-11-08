include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
    lvm_wt_tests.h \
    bin_map_stream_reader_tests.h \
    string_manipulations_tests.h \
    test_doubles/fake_lvm_wt_bin_map_store.h \
    fixtures/bin_map_stream_reader_special_lines_tests.h \
    bin_map_stream_line_fields_tests.h

SOURCES += \
        main.cpp

INCLUDEPATH += \
    $$PWD/..

LIBS += -L$$PWD/../../build
LIBS += -ltdd_kata_bin_mapping