#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "common/string_manipulations.h"
#include <string>

using Qx::CIString;

TEST( case_insensitive_string, equal_strings_should_be_equivalent )
{
    std::string lNormalString{ "lowercase string" };

    CIString lInsensitiveString{ "lowercase string" };

    ASSERT_TRUE( lNormalString == lInsensitiveString );
}

TEST( case_insensitive_string, case_different_strings_should_be_equivalent )
{
    std::string lNormalString{ "lowercase string" };

    CIString lInsensitiveString{ "LOWERCASE string" };

    ASSERT_TRUE( lNormalString == lInsensitiveString );
}