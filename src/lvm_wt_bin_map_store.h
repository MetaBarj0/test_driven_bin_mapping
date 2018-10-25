#ifndef LVM_WT_BIN_MAP_STORE_H
#define LVM_WT_BIN_MAP_STORE_H

#include <string>

namespace Qx
{
namespace BinMapping
{

class LvmWtBinMapItem;

class LvmWtBinMapStore
{
public :
    LvmWtBinMapStore( const std::string &aFilePath );

    LvmWtBinMapItem GetBinMapItemByKey( int aKey ) const;
};

}
}

#endif // LVM_WT_BIN_MAP_STORE_H