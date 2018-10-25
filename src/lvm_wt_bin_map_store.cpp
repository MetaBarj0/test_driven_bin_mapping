#include "lvm_wt_bin_map_store.h"
#include "lvm_wt_bin_map_item.h"
#include "common/exceptions.h"
#include "lvm_wt_exceptions.h"
#include "bin_map_file_reader.h"

namespace Qx
{
namespace BinMapping
{

LvmWtBinMapStore::LvmWtBinMapStore(const std::string &aFilePath)
{
    BinMapFileReader lFileReader{ aFilePath };
}

LvmWtBinMapItem LvmWtBinMapStore::GetBinMapItemByKey(int aKey) const
{
    ( void ) aKey;
    throw "Not implemented yet";
}

}
}