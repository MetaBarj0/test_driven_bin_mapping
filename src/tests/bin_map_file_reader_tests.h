#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "common/exceptions.h"
#include "bin_map_file_reader.h"

using Qx::BinMapping::BinMapFileReader;

TEST(bin_map_file_reader, instantiate_with_empty_file_path)
{
    ASSERT_THROW( BinMapFileReader{ "" }, Qx::BinMapping::EmptyFilePath );
}


TEST(bin_map_file_reader, instantiate_with_bad_file_path)
{
    ASSERT_THROW( BinMapFileReader{ "foo" }, Qx::BinMapping::BadFilePath );
}

TEST(bin_map_file_reader, instantiate_with_valid_path)
{
    BinMapFileReader lReader{ "bar" };

    ASSERT_TRUE( lReader.IsOpen() );
}