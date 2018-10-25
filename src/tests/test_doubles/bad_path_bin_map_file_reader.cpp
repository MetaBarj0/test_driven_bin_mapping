#include "bad_path_bin_map_file_reader.h"
#include "common/exceptions.h"

BadPathBinMapFileReader::BadPathBinMapFileReader(const std::string &)
{
    throw Qx::BinMapping::BadFilePath{};
}
