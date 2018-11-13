#include "lvm_wt_bin_map_item.h"

#include <utility>

namespace Qx
{
namespace BinMapping
{

LvmWtBinMapItem::LvmWtBinMapItem(std::string &&aTestName, int aTestNumber, int aBinNumber, std::string &&aBinName) noexcept :
    mTestName{ std::move( aTestName ) },
    mTestNumber{ aTestNumber },
    mBinNumber{ aBinNumber },
    mBinName{ std::move( aBinName ) } {}

const std::string & LvmWtBinMapItem::GetTestName() const noexcept
{
    return mTestName;
}

int LvmWtBinMapItem::GetTestNumber() const noexcept
{
    return mTestNumber;
}

int LvmWtBinMapItem::GetBinNumber() const noexcept
{
    return mBinNumber;
}

const std::string & LvmWtBinMapItem::GetBinName() const noexcept
{
    return mBinName;
}

}
}