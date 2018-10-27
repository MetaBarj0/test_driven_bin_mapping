QT = core

TEMPLATE = lib

CONFIG += c++14 staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    lvm_wt_bin_map_store.cpp \
    lvm_wt_bin_map_item.cpp \
    bin_map_stream_line.cpp

HEADERS += \
    lvm_wt_bin_map_store.h \
    lvm_wt_bin_map_item.h \
    lvm_wt_exceptions.h \
    common/exceptions.h \
    readable_binmap_content.h \
    bin_map_stream_reader.h \
    bin_map_stream_line.h \
    common/string_manipulations.h \
    common/storeable_bin_map.h