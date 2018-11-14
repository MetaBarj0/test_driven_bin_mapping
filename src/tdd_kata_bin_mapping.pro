QT = core

TEMPLATE = lib

CONFIG += c++14 lib shared

DEFINES += TDD_KATA_BIN_MAPPING_SHARED

macx-clang : QMAKE_CXXFLAGS += -fvisibility=hidden

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    lvm_wt/lvm_wt_bin_map_store.cpp \
    lvm_wt/lvm_wt_bin_map_item.cpp \
    common/bin_map_stream_line.cpp

HEADERS += \
    lvm_wt/lvm_wt_bin_map_store.h \
    lvm_wt/lvm_wt_bin_map_item.h \
    common/exceptions.h \
    common/readable_binmap_content.h \
    common/bin_map_stream_reader.h \
    common/bin_map_stream_line.h \
    common/string_manipulations.h \
    common/storeable_bin_map.h \
    common/bin_map_stream_line_fields.h \
    tdd_kata_bin_mapping.h