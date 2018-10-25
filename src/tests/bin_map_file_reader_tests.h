#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "common/exceptions.h"
#include "bin_map_file_reader.h"
#include "test_doubles/valid_path_bin_map_file_reader.h"
#include "test_doubles/bad_path_bin_map_file_reader.h"
#include "test_doubles/empty_path_bin_map_file_reader.h"

using Qx::BinMapping::BinMapFileReader;

TEST(bin_map_file_reader, instantiate_with_empty_file_path)
{
    ASSERT_THROW( EmptyPathBinMapFileReader{ "" }, Qx::BinMapping::EmptyFilePath );
}


TEST(bin_map_file_reader, instantiate_with_bad_file_path)
{
    ASSERT_THROW( BadPathBinMapFileReader{ "foo" }, Qx::BinMapping::BadFilePath );
}

TEST(bin_map_file_reader, instantiate_with_valid_path)
{
    ValidPathBinMapFileReader lReader{ "bar" };

    ASSERT_TRUE( lReader.IsOpen() );
}