#ifndef LVM_WT_BIN_MAP_STORE_H
#define LVM_WT_BIN_MAP_STORE_H

#include <string>

namespace Qx
{
namespace BinMapping
{

struct ReadableBinMapContent;

class LvmWtBinMapItem;

class LvmWtBinMapStore
{
public :
    LvmWtBinMapStore( std::unique_ptr< ReadableBinMapContent > &&aBinMapFileReader );

    LvmWtBinMapItem GetBinMapItemByKey( int aKey ) const;
    bool IsEmpty() const noexcept;

private :
    std::unique_ptr< ReadableBinMapContent > mFileReader;
};

}
}

#endif // LVM_WT_BIN_MAP_STORE_H