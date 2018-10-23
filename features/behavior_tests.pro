TEMPLATE = app

CONFIG += c++14

CONFIG -= app_bundle

# cucumber dependency
CUCUMBER_CPP_ROOT_DIR = $(CUCUMBER_CPP_ROOT_DIR)

! exists( $$CUCUMBER_CPP_ROOT_DIR ) {
    error("The variable CUCUMBER_CPP_ROOT_DIR is undefined or points toward a wrong directory path.")
    error("This variable is mandatory and contain the path of the root directory where cucumber-cpp is located.")
    error("Either define this variable in your environment or add it to the project build environment")
}

CUCUMBER_CPP_LIB_DIR = $$CUCUMBER_CPP_ROOT_DIR/lib
CUCUMBER_CPP_INC_DIR = $$CUCUMBER_CPP_ROOT_DIR/include

! exists( $$CUCUMBER_CPP_LIB_DIR ) {
    error("Cannot find the lib directory of cucumber-cpp under $$CUCUMBER_CPP_ROOT_DIR")
}

! exists(CUCUMBER_CPP_INC_DIR)) {
    error("Cannot find the include directory of cucumber-cpp under $$CUCUMBER_CPP_ROOT_DIR")
}

INCLUDEPATH += $$CUCUMBER_CPP_INC_DIR
LIBS += -L$$CUCUMBER_CPP_LIB_DIR
LIBS += -lcucumber-cpp

# need that one to solve an undefined symbol issue
SOURCES += $$PWD/../cucumber-cpp/src/drivers/GTestDriver.cpp

# boost dependency
BOOST_ROOT_DIR = $(BOOST_ROOT_DIR)

! exists( $$BOOST_ROOT_DIR ) {
    error("The variable BOOST_ROOT_DIR is undefined or points toward a wrong directory path.")
    error("This variable is mandatory and contain the path of the root directory where boost is located.")
    error("Either define this variable in your environment or add it to the project build environment")
}

BOOST_INC_DIR = $$BOOST_ROOT_DIR/include
BOOST_LIB_DIR = $$BOOST_ROOT_DIR/lib

INCLUDEPATH += $$BOOST_INC_DIR

LIBS += -L$$BOOST_LIB_DIR
LIBS += \
    -lboost_filesystem \
    -lboost_regex \
    -lboost_program_options \
    -lboost_chrono \
    -lboost_system

# googletest dependency
include( $$PWD/../src/tests/gtest_dependency.pri )

# step definitions
SOURCES += \
    step_definitions/calc.cpp

DISTFILES += \
    addition.feature