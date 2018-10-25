#include "bin_map_file_reader.h"
#include "lvm_wt_exceptions.h"

namespace Qx
{
namespace BinMapping
{

BinMapFileReader::BinMapFileReader(const std::string &aFilePath)
{
    if( aFilePath.empty() )
        throw EmptyFilePath{};
}

}
}