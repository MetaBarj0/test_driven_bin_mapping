#include "lvm_wt_bin_map_store.h"
#include "lvm_wt_bin_map_item.h"
#include "common/exceptions.h"
#include "lvm_wt_exceptions.h"
#include "readable_binmap_content.h"
#include "bin_map_file_reader.h"

#include <memory>

namespace Qx
{
namespace BinMapping
{

LvmWtBinMapStore::LvmWtBinMapStore( std::unique_ptr< ReadableBinMapContent > &&aBinMapFileReader ) :
    mFileReader{ std::move( aBinMapFileReader ) } { }

LvmWtBinMapItem LvmWtBinMapStore::GetBinMapItemByKey(int aKey) const
{
    ( void ) aKey;
    throw "Not implemented yet";
}

}
}