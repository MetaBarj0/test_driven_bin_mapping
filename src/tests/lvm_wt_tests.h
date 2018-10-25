#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "lvm_wt_bin_map_store.h"
#include "lvm_wt_exceptions.h"
#include "common/exceptions.h"
#include "test_doubles/bad_path_bin_map_file_reader.h"
#include "test_doubles/empty_path_bin_map_file_reader.h"
#include "test_doubles/valid_path_bin_map_file_reader.h"

using namespace testing;

using Qx::BinMapping::LvmWtBinMapStore;
using Qx::BinMapping::EmptyFilePath;
using Qx::BinMapping::BadFilePath;

TEST(lvm_wt, instantiate_bin_map_store_with_empty_file_path)
{
    ASSERT_THROW( LvmWtBinMapStore{ std::make_unique< EmptyPathBinMapFileReader >( "" ) },
                  EmptyFilePath );
}

TEST(lvm_wt, instantiate_bin_map_store_with_invalid_file_path)
{
    ASSERT_THROW( LvmWtBinMapStore{ std::make_unique< BadPathBinMapFileReader >( "foo" ) },
                  BadFilePath );
}

TEST(lvm_wt, DISABLED_instantiate_bin_map_store_with_valid_file_path)
{
   LvmWtBinMapStore store{ std::make_unique< ValidPathBinMapFileReader >( "bar" ) };

   /// TODO - activate this test asap, once unstuck
   /// ASSERT_FALSE( store.IsEmpty() );
}