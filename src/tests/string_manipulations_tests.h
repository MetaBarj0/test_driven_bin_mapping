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