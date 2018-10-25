#include "lvm_wt_bin_map_store.h"
#include "lvm_wt_bin_map_item.h"
#include "lvm_wt_exceptions.h"

namespace Qx
{
namespace BinMapping
{

LvmWtBinMapStore::LvmWtBinMapStore(const std::string &aFilePath)
{
    if( aFilePath.empty() )
        throw EmptyFilePath{};
}

LvmWtBinMapItem LvmWtBinMapStore::GetBinMapItemByKey(int aKey) const
{
    ( void ) aKey;
    throw "Not implemented yet";
}

}
}