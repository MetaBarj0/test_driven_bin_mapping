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

# some useful macro are missing for some Gherkin language keywords
DEFINES += AND=CUKE_STEP_ BUT=CUKE_STEP_