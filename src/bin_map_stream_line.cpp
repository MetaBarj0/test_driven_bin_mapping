#include "bin_map_stream_line.h"

#include <utility>

namespace Qx
{
namespace BinMapping
{

BinMapStreamLine::BinMapStreamLine( std::string &&aContent, bool aIsHeader ) noexcept :
    mContent{ std::move( aContent ) },
    mIsHeader{ aIsHeader } {}

std::string BinMapStreamLine::ToString() const noexcept
{
    return mContent;
}

bool BinMapStreamLine::IsHeader() const noexcept
{
    return mIsHeader;
}

}
}
