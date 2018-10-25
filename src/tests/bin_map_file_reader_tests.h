#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "lvm_wt_exceptions.h"

TEST(bin_map_file_reader, instantiate_with_empty_file_path)
{
    ASSERT_THROW( Qx::BinMapping::BinMapFileReader{ "" }, Qx::BinMapping::EmptyFilePath );
}