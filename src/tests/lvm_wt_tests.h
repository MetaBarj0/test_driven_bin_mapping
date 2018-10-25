#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "lvm_wt_bin_map_store.h"
#include "lvm_wt_exceptions.h"
#include "common/exceptions.h"

using namespace testing;

TEST(lvm_wt, instantiate_bin_map_store_with_empty_file_path)
{
    ASSERT_THROW( Qx::BinMapping::LvmWtBinMapStore{ "" }, Qx::BinMapping::EmptyFilePath );
}

TEST(lvm_wt, instantiate_bin_map_store_with_invalid_file_path)
{
    ASSERT_THROW( Qx::BinMapping::LvmWtBinMapStore{ "foo" }, Qx::BinMapping::BadFilePath );
}

TEST(lvm_wt, DISABLED_instantiate_bin_map_store_with_valid_file_path)
{
   Qx::BinMapping::LvmWtBinMapStore store{ "bar" };

   /// TODO - activate this test asap, once unstuck
   /// ASSERT_FALSE( store.IsEmpty() );
}