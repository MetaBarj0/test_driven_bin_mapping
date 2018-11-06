#include "lvm_wt_tests.h"
#include "bin_map_stream_reader_tests.h"
#include "string_manipulations_tests.h"
#include "fixtures/bin_map_stream_reader_special_lines_tests.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
