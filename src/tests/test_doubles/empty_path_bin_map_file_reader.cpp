#include "empty_path_bin_map_file_reader.h"
#include "common/exceptions.h"

EmptyPathBinMapFileReader::EmptyPathBinMapFileReader(const std::string &)
{
    throw Qx::BinMapping::EmptyFilePath{};
}