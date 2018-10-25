#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "lvm_wt_bin_map_store.h"

using namespace testing;

TEST(lvm_wt, instantiate_bin_map_store_with_empty_file_path)
{
    ASSERT_THROW( Qx::BinMapping::LvmWtBinMapStore{ "" }, Qx::BinMapping::EmptyFilePath );
}
