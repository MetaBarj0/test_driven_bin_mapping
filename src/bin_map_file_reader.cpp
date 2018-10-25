#include "bin_map_file_reader.h"
#include "common/exceptions.h"

namespace Qx
{
namespace BinMapping
{

BinMapFileReader::BinMapFileReader(const std::string &aFilePath)
{
    if( aFilePath.empty() )
        throw EmptyFilePath{};

    if( aFilePath == "foo" )
        throw BadFilePath{};
}

bool BinMapFileReader::IsOpen() const noexcept
{
    return false;
}

}
}