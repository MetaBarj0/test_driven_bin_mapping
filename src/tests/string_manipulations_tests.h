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

TEST( string_manipulations, empty_string_start_with_always_fail )
{
    Qx::CIString lEmptyStr;

    ASSERT_FALSE( Qx::StringStartsWith( lEmptyStr, "starting of a string" ) );
}


TEST( string_manipulations, one_char_string_start_with_same_char )
{
    Qx::CIString lString{ "a" };

    ASSERT_TRUE( Qx::StringStartsWith( lString, "a" ) );
}