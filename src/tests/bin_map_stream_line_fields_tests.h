#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "bin_map_stream_line_fields.h"
#include "test_doubles/fake_lvm_wt_bin_map_store.h"

#include <string>

using Qx::BinMapping::BinMapStreamLineFields;

TEST( bin_map_stream_line_fields, empty_line_gives_no_fields )
{
    std::string lLine;
    FakeLvmWtBinMapStore lStore;

    BinMapStreamLineFields< int > lFields{ lStore, lLine };

    ASSERT_TRUE( lFields.IsEmpty() );
}

TEST( bin_map_stream_line_fields, no_fields_if_any_type_is_wrong )
{
    std::string lLine{ "foo, bar, 3.141597" };
    FakeLvmWtBinMapStore lStore;

    BinMapStreamLineFields< std::string, bool, double > lFields{ lStore, lLine };

    ASSERT_TRUE( lFields.IsEmpty() );
}

TEST( bin_map_stream_line_fields, no_fields_if_type_list_is_lesser_than_line_fields )
{
    std::string lLine{ "foo, bar, 3.141597" };
    FakeLvmWtBinMapStore lStore;

    BinMapStreamLineFields< std::string, std::string >lFields{ lStore, lLine };

    ASSERT_TRUE( lFields.IsEmpty() );
}

TEST( bin_map_stream_line_fields, no_fields_if_type_list_is_greater_than_line_fields )
{
    std::string lLine{ "foo, bar, 3.141597" };
    FakeLvmWtBinMapStore lStore;

    BinMapStreamLineFields< std::string, std::string, double, int >lFields{ lStore, lLine };

    ASSERT_TRUE( lFields.IsEmpty() );
}

TEST( bin_map_stream_line_fields, correct_mapping_between_line_and_type_list_give_fields )
{
    std::string lLine{ "foo, bar, 3.141597, 42" };

    FakeLvmWtBinMapStore lStore;

    BinMapStreamLineFields< std::string, std::string, double, int >lFields{ lStore, lLine };

    ASSERT_FALSE( lFields.IsEmpty() );
}

TEST( bin_map_stream_line_fields, obtain_first_field_value_for_unique_field )
{
    std::string lLine{ "true" };

    FakeLvmWtBinMapStore lStore;

    BinMapStreamLineFields< bool >lFields{ lStore, lLine };

    ASSERT_THAT( lFields[ 0 ], testing::Eq( true ) );
}

TEST( bin_map_stream_line_fields, out_of_range_index_for_field_value_must_throw )
{
    std::string lLine{ "true" };

    FakeLvmWtBinMapStore lStore;

    BinMapStreamLineFields< bool >lFields{ lStore, lLine };

    ASSERT_THROW( lFields[ 42 ], Qx::BinMapping::OutOfRangeFieldIndex );
}