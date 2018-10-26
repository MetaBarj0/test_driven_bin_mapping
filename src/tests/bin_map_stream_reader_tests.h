#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "common/exceptions.h"
#include "bin_map_stream_reader.h"
#include "bin_map_stream_line.h"

#include <sstream>

using BinMapStreamReader = Qx::BinMapping::BinMapStreamReader< std::stringstream >;
using Qx::BinMapping::BinMapStreamLine;

TEST(bin_map_stream_reader, instantiate_with_empty_stream)
{
    ASSERT_THROW( BinMapStreamReader{ std::stringstream{} }, Qx::BinMapping::InvalidStream);
}

TEST(bin_map_stream_reader, instantiate_with_valid_stream)
{
    std::stringstream lStream;
    lStream << "foo," << "bar," << "baz\n";

    ASSERT_NO_THROW( BinMapStreamReader { std::move( lStream ) } );
}

static void TestExtractedLineEquals( const BinMapStreamReader &aReader, const char *aText )
{
    BinMapStreamLine lLine = aReader.GetLine( '\n' );

    ASSERT_THAT( lLine.ToString(), testing::StrEq( aText ) );
}

TEST( bin_map_stream_reader, extract_line )
{
    std::stringstream lStream;
    lStream << "a line\n";
    lStream << "another line";
    lStream << " that is longer\n";

    BinMapStreamReader lReader{ std::move( lStream ) };

    TestExtractedLineEquals( lReader, "a line" );
    TestExtractedLineEquals( lReader, "another line that is longer" );
}

TEST( bin_map_stream_reader, DISABLED_extract_header )
{
    std::stringstream lStream;
    lStream << "Test Name,STD TEST NUMBERS,Assigned  BIN#,Bin Name\n";
    lStream << " GS SHORT,5,29,GS SHORT\n";
    lStream << "Test Name,STD TEST NUMBERS,Assigned  BIN#,Bin Name\n";

    BinMapStreamReader lReader{ std::move( lStream ) };

    ASSERT_TRUE( lReader.GetLine( '\n' ).IsHeader() );
    ASSERT_FALSE( lReader.GetLine( '\n' ).IsHeader() );
    ASSERT_FALSE( lReader.GetLine( '\n' ).IsHeader() );
}