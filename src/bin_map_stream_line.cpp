#include "bin_map_stream_line.h"

#include <utility>

namespace Qx
{
namespace BinMapping
{

BinMapStreamLine::BinMapStreamLine(const std::string &aContent, BinMapStreamLineKinds aKind ) noexcept :
    mContent{ aContent },
    mKind{ aKind } {}

std::string BinMapStreamLine::ToString() const noexcept
{
    return mContent;
}

bool BinMapStreamLine::IsHeader() const noexcept
{
    return mKind == BinMapStreamLineKinds::header;
}

bool BinMapStreamLine::IsComment() const noexcept
{
    return mKind == BinMapStreamLineKinds::comment;
}

}
}
