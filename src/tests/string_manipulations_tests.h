#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "common/string_manipulations.h"
#include <string>

using Qx::CaseInsensitiveString;

TEST( case_insensitive_string, equals_string_should_be_equivalent )
{
    std::string lNormalString{ "lowercase string" };

    CaseInsensitiveString lInsensitiveString{ "lowercase string" };

    ASSERT_THAT( lNormalString, testing::StrEq( lInsensitiveString ) );
}