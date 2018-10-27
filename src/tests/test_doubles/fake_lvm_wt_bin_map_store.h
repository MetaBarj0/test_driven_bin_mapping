#pragma once

#include "common/storeable_bin_map.h"

struct FakeLvmWtBinMapStore : public Qx::BinMapping::StoreableBinMap
{
    Qx::CIString GetHeaderLineStart() const noexcept override
    { return { "test name" }; }

    char GetFieldDelimiter() const noexcept override
    { return ','; }

    char GetEndOfLine() const noexcept override
    { return '\n'; }

    void SetHeaderLineDetectedToggle() noexcept override
    { mIsHeaderLineDetected = true; }

    bool IsHeaderLineDetected() const noexcept override
    { return mIsHeaderLineDetected; }

private :
    bool mIsHeaderLineDetected = false;
};