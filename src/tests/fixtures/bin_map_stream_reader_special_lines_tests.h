#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "test_doubles/fake_lvm_wt_bin_map_store.h"
#include "bin_map_stream_reader.h"

#include <memory>
#include <sstream>
#include <utility>
#include <string>

class bin_map_stream_reader_special_lines : public ::testing::Test
{
public :
    using BinMapStreamReader = Qx::BinMapping::BinMapStreamReader< std::stringstream >;

public :
    void TearDown() override { mStreamReader.reset( nullptr ); }

    void UseStreamForTest( std::stringstream &&aStream )
    {
        mStreamReader.reset( new BinMapStreamReader( std::move( aStream ) ) );
    }

    const BinMapStreamReader & GetStreamReaderToTest() const noexcept { return *mStreamReader; }
    FakeLvmWtBinMapStore & GetModifiableMockedStore() noexcept { return mStore; }

private :
    FakeLvmWtBinMapStore mStore;
    std::unique_ptr< BinMapStreamReader > mStreamReader;
};

TEST_F( bin_map_stream_reader_special_lines, extract_header_correctly )
{
    std::stringstream lStream;
    lStream << "Test Name,STD TEST NUMBERS,Assigned  BIN#,Bin Name\n";
    lStream << " GS SHORT,5,29,GS SHORT\n";
    lStream << "Test Name,STD TEST NUMBERS,Assigned  BIN#,Bin Name\n";

    UseStreamForTest( std::move( lStream ) );

    ASSERT_TRUE( GetStreamReaderToTest().GetLineFor( GetModifiableMockedStore() ).IsHeader() );
    ASSERT_FALSE( GetStreamReaderToTest().GetLineFor( GetModifiableMockedStore() ).IsHeader() );
    ASSERT_FALSE( GetStreamReaderToTest().GetLineFor( GetModifiableMockedStore() ).IsHeader() );
}

TEST_F( bin_map_stream_reader_special_lines, empty_line_is_not_a_comment )
{
    std::stringstream lStream;

    lStream << "\n";

    UseStreamForTest( std::move( lStream ) );

    ASSERT_FALSE( GetStreamReaderToTest().GetLineFor( GetModifiableMockedStore() ).IsComment() );
}

TEST_F( bin_map_stream_reader_special_lines, comment_symbol_starting_line_is_a_comment )
{
    std::stringstream lStream;

    lStream << "# a comment\n";

    UseStreamForTest( std::move( lStream ) );

    ASSERT_TRUE( GetStreamReaderToTest().GetLineFor( GetModifiableMockedStore() ).IsComment() );
}

TEST_F( bin_map_stream_reader_special_lines, spaces_and_comment_symbol_starting_line_is_a_comment )
{
    std::stringstream lStream;

    lStream << "  # spaces an comment symbol is a comment\n";

    UseStreamForTest( std::move( lStream ) );

    ASSERT_TRUE( GetStreamReaderToTest().GetLineFor( GetModifiableMockedStore() ).IsComment() );
}

TEST_F( bin_map_stream_reader_special_lines, empty_line_gives_no_fields )
{
    std::stringstream lStream;
    lStream << '\n';

    UseStreamForTest( std::move( lStream ) );

    const auto &lFields =
        GetStreamReaderToTest().GetLineFor( GetModifiableMockedStore() )
        .ToFields< std::string, int, int, std::string >( GetModifiableMockedStore() );

    ASSERT_TRUE( lFields.IsEmpty() );
}