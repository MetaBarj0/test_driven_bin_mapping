#ifndef LVM_WT_BIN_MAP_STORE_H
#define LVM_WT_BIN_MAP_STORE_H

#include "common/storeable_bin_map.h"
#include "common/string_manipulations.h"
#include "lvm_wt_bin_map_item.h"

#include <string>
#include <vector>

namespace Qx
{
namespace BinMapping
{

struct ReadableBinMapContent;

class LvmWtBinMapStore : public StoreableBinMap
{
public :
    LvmWtBinMapStore( std::unique_ptr< ReadableBinMapContent > &&aBinMapFileReader );

    LvmWtBinMapItem GetBinMapItemByKey( int aKey ) const;
    bool IsEmpty() const noexcept;
    Qx::CIString GetHeaderLineStart() const noexcept override;
    char GetCommentLineStart() const noexcept override;
    char GetFieldDelimiter() const noexcept override;
    char GetEndOfLine() const noexcept override;
    void SetHeaderLineDetectedToggle() noexcept override;
    bool IsHeaderLineDetected() const noexcept override;

private :
    std::unique_ptr< ReadableBinMapContent > mFileReader;
    bool mIsHeaderLineDetected = false;
    std::vector< LvmWtBinMapItem > mItems;
};

}
}

#endif // LVM_WT_BIN_MAP_STORE_H