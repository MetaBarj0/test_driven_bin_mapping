#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "lvm_wt_bin_map_store.h"
#include "lvm_wt_exceptions.h"
#include "common/exceptions.h"
#include "bin_map_stream_reader.h"

#include <sstream>

using namespace testing;

using Qx::BinMapping::LvmWtBinMapStore;
using Qx::BinMapping::InvalidStream;

using BinMapStreamReader = Qx::BinMapping::BinMapStreamReader< std::stringstream >;

TEST(lvm_wt, instantiate_bin_map_store_with_empty_stream_reader)
{
    ASSERT_THROW( LvmWtBinMapStore{ std::make_unique< BinMapStreamReader >( std::stringstream{} ) },
                  InvalidStream );
}

TEST(lvm_wt, instantiate_bin_map_store_with_invalid_stream_content )
{
    std::stringstream lStream;
    lStream << "foo," << "bar," << "baz\n";



    ASSERT_THROW( LvmWtBinMapStore{ std::make_unique< BinMapStreamReader >( std::move( lStream ) ) },
                  InvalidStream );
}

TEST( lvm_wt, DISABLED_instantiate_bin_map_store_with_valid_stream_content )
{
    std::stringstream lValidStream;
    lValidStream << "Test Name,STD TEST NUMBERS,Assigned  BIN#,Bin Name\n";
    lValidStream << " GS SHORT,5,29,GS SHORT\n";

    LvmWtBinMapStore lStore{ std::make_unique< BinMapStreamReader >( std::move( lValidStream ) ) };

    ASSERT_TRUE( ! lStore.IsEmpty() );
}