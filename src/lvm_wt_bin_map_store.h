#ifndef LVM_WT_BIN_MAP_STORE_H
#define LVM_WT_BIN_MAP_STORE_H

#include "common/storeable_bin_map.h"
#include "common/string_manipulations.h"

#include <string>

namespace Qx
{
namespace BinMapping
{

struct ReadableBinMapContent;

class LvmWtBinMapItem;

class LvmWtBinMapStore : public StoreableBinMap
{
public :
    LvmWtBinMapStore( std::unique_ptr< ReadableBinMapContent > &&aBinMapFileReader );

    LvmWtBinMapItem GetBinMapItemByKey( int aKey ) const;
    bool IsEmpty() const noexcept;
    Qx::CIString GetHeaderLineStart() const noexcept override;
    char GetFieldDelimiter() const noexcept override;
    char GetEndOfLine() const noexcept override;
    void SetHeaderLineDetectedToggle() noexcept override;
    bool IsHeaderLineDetected() const noexcept override;

private :
    std::unique_ptr< ReadableBinMapContent > mFileReader;
    bool mIsHeaderLineDetected = false;
};

}
}

#endif // LVM_WT_BIN_MAP_STORE_H