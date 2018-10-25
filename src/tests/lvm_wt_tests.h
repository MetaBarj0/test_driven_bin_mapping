#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "lvm_wt_bin_map_store.h"
#include "lvm_wt_exceptions.h"
#include "common/exceptions.h"
#include "bin_map_file_reader.h"

using namespace testing;

using Qx::BinMapping::BinMapFileReader;
using Qx::BinMapping::LvmWtBinMapStore;
using Qx::BinMapping::EmptyFilePath;
using Qx::BinMapping::BadFilePath;

TEST(lvm_wt, instantiate_bin_map_store_with_empty_file_path)
{
    ASSERT_THROW( LvmWtBinMapStore{ std::make_unique< BinMapFileReader >( "" ) },
                  EmptyFilePath );
}

TEST(lvm_wt, instantiate_bin_map_store_with_invalid_file_path)
{
    ASSERT_THROW( LvmWtBinMapStore{ std::make_unique< BinMapFileReader >( "foo" ) },
                  BadFilePath );
}

TEST(lvm_wt, DISABLED_instantiate_bin_map_store_with_valid_file_path)
{
   LvmWtBinMapStore store{ std::make_unique< BinMapFileReader >( "bar" ) };

   /// TODO - activate this test asap, once unstuck
   /// ASSERT_FALSE( store.IsEmpty() );
}