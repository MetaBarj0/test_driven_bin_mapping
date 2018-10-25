#pragma once

#include "readable_binmap_content.h"

#include <string>

class ValidPathBinMapFileReader : public Qx::BinMapping::ReadableBinMapContent
{
public :
    ValidPathBinMapFileReader( const std::string & ) noexcept;

    bool IsOpen() const noexcept override;
};