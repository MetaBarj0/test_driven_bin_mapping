#ifndef BIN_MAP_FILE_READER_H
#define BIN_MAP_FILE_READER_H

#include <string>

#include "readable_binmap_content.h"

namespace Qx
{
namespace BinMapping
{

class BinMapFileReader : public ReadableBinMapContent
{
public :
    BinMapFileReader( const std::string &aFilePath );

    bool IsOpen() const noexcept override;
};

}
}

#endif // BIN_MAP_FILE_READER_H