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

TEST( bin_map_stream_line_fields, line_with_one_fields_gives_fields_with_correct_type )
{
    std::string lLine{ "42" };
    FakeLvmWtBinMapStore lStore;

    BinMapStreamLineFields< int > lFields{ lStore, lLine };

    ASSERT_FALSE( lFields.IsEmpty() );
}

TEST( bin_map_stream_line_fields, line_with_one_fields_gives_no_fields_with_incorrect_type )
{
    std::string lLine{ "foo" };
    FakeLvmWtBinMapStore lStore;

    BinMapStreamLineFields< int > lFields{ lStore, lLine };

    ASSERT_TRUE( lFields.IsEmpty() );
}

TEST( bin_map_stream_line_fields, line_with_two_fields_give_fields_with_correct_types )
{
    std::string lLine{ "42, 3.141597" };
    FakeLvmWtBinMapStore lStore;

    BinMapStreamLineFields< int, double > lFields{ lStore, lLine };

    ASSERT_FALSE( lFields.IsEmpty() );
}

TEST( bin_map_stream_line_fields, line_with_two_fields_give_no_fields_with_incorrect_types )
{
    std::string lLine{ "foo, 0" };
    FakeLvmWtBinMapStore lStore;

    BinMapStreamLineFields< int, std::string > lFields{ lStore, lLine };

    ASSERT_TRUE( lFields.IsEmpty() );
}
