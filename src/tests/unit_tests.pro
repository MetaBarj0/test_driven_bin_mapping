include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
    lvm_wt_tests.h \
    bin_map_file_reader_tests.h \
    test_doubles/empty_path_bin_map_file_reader.h \
    test_doubles/bad_path_bin_map_file_reader.h \
    test_doubles/valid_path_bin_map_file_reader.h

SOURCES += \
        main.cpp \
    test_doubles/empty_path_bin_map_file_reader.cpp \
    test_doubles/bad_path_bin_map_file_reader.cpp \
    test_doubles/valid_path_bin_map_file_reader.cpp

INCLUDEPATH += \
    $$PWD/..

LIBS += -L$$PWD/../../build
LIBS += -ltdd_kata_bin_mapping