#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "common/string_manipulations.h"
#include <string>

using Qx::CIString;

TEST( case_insensitive_string, equal_strings_should_be_equivalent )
{
    Qx::CIString lCaseInsensitiveString{ "lowercase string" };

    ASSERT_TRUE( lCaseInsensitiveString == "lowercase string" );
}

TEST( case_insensitive_string, case_different_strings_should_be_equivalent )
{
    Qx::CIString lCaseInsensitiveString{ "lowercase string" };

    ASSERT_TRUE( lCaseInsensitiveString == "LOWERCASE string" );
}

TEST( string_manipulations, empty_string_starts_with_always_fail )
{
    Qx::CIString lEmptyStr;

    ASSERT_FALSE( Qx::StringStartsWith( lEmptyStr, "starting of a string" ) );
}

TEST( string_manipulations, one_char_string_starts_with_same_char )
{
    Qx::CIString lString{ "a" };

    ASSERT_TRUE( Qx::StringStartsWith( lString, "a" ) );
}

TEST( string_manipulations, multiple_char_string_starts_with )
{
    Qx::CIString lString{ "aBa" };

    ASSERT_TRUE( Qx::StringStartsWith( lString, "ab" ) );
}


TEST( string_manipulations, same_size_strings_with_different_chars)
{
    Qx::CIString lString{ "abcd" };

    ASSERT_FALSE( Qx::StringStartsWith( lString, "aabc" ) );
}

TEST( string_manipulations, non_empty_string_empty_pattern)
{
    Qx::CIString lString{ "abcd" };

    ASSERT_TRUE( Qx::StringStartsWith( lString, "" ) );
}

TEST( string_manipulations, empty_string_empty_pattern)
{
    Qx::CIString lString{ "" };

    ASSERT_TRUE( Qx::StringStartsWith( lString, "" ) );
}

TEST( string_manipulations, trim_an_empty_string_left_side_of_spaces_gives_an_empty_string )
{
    Qx::CIString lEmptyString;

    ASSERT_TRUE( lEmptyString == Qx::TrimStringLeftSideOf( lEmptyString, ' ' ) );
}

TEST( string_manipulations, trim_a_string_without_spaces_left_side_of_spaces_gives_the_same_string )
{
    Qx::CIString lString{ "a string without spaces at left side   " };

    ASSERT_TRUE( lString == Qx::TrimStringLeftSideOf( lString, ' ' ) );
}