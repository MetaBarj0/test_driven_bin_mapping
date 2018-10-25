#include "lvm_wt_bin_map_store.h"
#include "lvm_wt_bin_map_item.h"
#include "common/exceptions.h"
#include "lvm_wt_exceptions.h"

namespace Qx
{
namespace BinMapping
{

LvmWtBinMapStore::LvmWtBinMapStore(const std::string &aFilePath)
{
    if( aFilePath.empty() )
        throw EmptyFilePath{};

    if( aFilePath == "foo" )
        throw BadFilePath{};
}

LvmWtBinMapItem LvmWtBinMapStore::GetBinMapItemByKey(int aKey) const
{
    ( void ) aKey;
    throw "Not implemented yet";
}

}
}