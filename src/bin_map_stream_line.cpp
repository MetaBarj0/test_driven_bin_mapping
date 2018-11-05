#include "bin_map_stream_line.h"

#include <utility>

namespace Qx
{
namespace BinMapping
{

BinMapStreamLine::BinMapStreamLine(const std::string &aContent, bool aIsHeader , bool aIsComment) noexcept :
    mContent{ aContent },
    mIsHeader{ aIsHeader },
    mIsComment{ aIsComment } {}

std::string BinMapStreamLine::ToString() const noexcept
{
    return mContent;
}

bool BinMapStreamLine::IsHeader() const noexcept
{
    return mIsHeader;
}

bool BinMapStreamLine::IsComment() const noexcept
{
    return mIsComment;
}

}
}
