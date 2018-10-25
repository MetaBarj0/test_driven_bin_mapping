#pragma once

#include "readable_binmap_content.h"

#include <string>

class BadPathBinMapFileReader : public Qx::BinMapping::ReadableBinMapContent
{
public :
    BadPathBinMapFileReader( const std::string & );
};