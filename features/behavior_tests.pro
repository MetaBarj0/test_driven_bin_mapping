TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle

include( cucumber_dependencies.pri )
include( boost_dependencies.pri )
include( googletest_dependencies.pri )

# step definitions
SOURCES += \
    step_definitions/bin_map_item_retrieval_lvm_wt.cpp

DISTFILES += \
    bin_map_item_retrieval_lvm_wt.feature \
    bin_map_items_lvm_wt.csv

# production code paths and libs
INCLUDEPATH += \
    $$PWD/../src \
    $$PWD/../src/common \
    $$PWD/../src/lvm_wt

LIBS += -L$$PWD/../build
LIBS += -ltdd_kata_bin_mapping

# directory of input files
DEFINES += INPUT_FILES_DIR=\\\"$$PWD/\\\"