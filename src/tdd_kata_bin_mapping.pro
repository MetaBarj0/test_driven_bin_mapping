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
    lvm_wt_bin_map_item.cpp

HEADERS += \
    lvm_wt_bin_map_store.h \
    lvm_wt_bin_map_item.h \
    lvm_wt_exceptions.h