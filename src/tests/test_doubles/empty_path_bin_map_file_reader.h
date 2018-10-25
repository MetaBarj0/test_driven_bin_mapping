#pragma once

#include "readable_binmap_content.h"

#include <string>

class EmptyPathBinMapFileReader : public Qx::BinMapping::ReadableBinMapContent
{
public :
    EmptyPathBinMapFileReader( const std::string & );

    bool IsOpen() const noexcept override;
};