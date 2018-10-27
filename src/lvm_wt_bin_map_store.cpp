#include "lvm_wt_bin_map_store.h"
#include "lvm_wt_bin_map_item.h"
#include "common/exceptions.h"
#include "lvm_wt_exceptions.h"
#include "bin_map_stream_reader.h"
#include "common/string_manipulations.h"

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

bool LvmWtBinMapStore::IsEmpty() const noexcept
{
    return true;
}

Qx::CIString LvmWtBinMapStore::GetHeaderLineStart() const noexcept
{
    return { "test name" };
}

char LvmWtBinMapStore::GetFieldDelimiter() const noexcept
{
    return ',';
}

char LvmWtBinMapStore::GetEndOfLine() const noexcept
{
    return '\n';
}

void LvmWtBinMapStore::SetHeaderLineDetectedToggle() noexcept
{
    mIsHeaderLineDetected = true;
}

bool LvmWtBinMapStore::IsHeaderLineDetected() const noexcept
{
    return  mIsHeaderLineDetected;
}

}
}