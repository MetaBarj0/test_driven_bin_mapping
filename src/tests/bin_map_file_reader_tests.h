#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "common/exceptions.h"
#include "bin_map_file_reader.h"

TEST(bin_map_file_reader, instantiate_with_empty_file_path)
{
    ASSERT_THROW( Qx::BinMapping::BinMapFileReader{ "" }, Qx::BinMapping::EmptyFilePath );
}


TEST(bin_map_file_reader, instantiate_with_bad_file_path)
{
    ASSERT_THROW( Qx::BinMapping::BinMapFileReader{ "foo" }, Qx::BinMapping::BadFilePath );
}