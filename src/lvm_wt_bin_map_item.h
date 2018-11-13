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
    LvmWtBinMapItem( std::string &&aTestName, int aTestNumber, int aBinNumber, std::string &&aBinName ) noexcept;

    const std::string & GetTestName() const noexcept;
    int GetTestNumber() const noexcept;
    int GetBinNumber() const noexcept;
    const std::string & GetBinName() const noexcept;

public :
    enum : std::size_t
    {
        test_name_field = 0,
        test_number_field,
        bin_number_field,
        bin_name_field
    };

private :
    std::string mTestName;
    int mTestNumber;
    int mBinNumber;
    std::string mBinName;
};

}
}


#endif // LVM_WT_BIN_MAP_ITEM_H