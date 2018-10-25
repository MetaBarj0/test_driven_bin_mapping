#ifndef LVM_WT_BIN_MAP_ITEM_H
#define LVM_WT_BIN_MAP_ITEM_H

#include <string>

namespace Qx
{
namespace BinMapping
{

class LvmWtBinMapItem
{
public :
    std::string GetTestName() const;
    int GetBinNumber() const;
    std::string GetBinName() const;
};

}
}


#endif // LVM_WT_BIN_MAP_ITEM_H