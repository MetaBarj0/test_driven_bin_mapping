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
