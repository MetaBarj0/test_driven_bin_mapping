#include "bin_map_stream_line.h"

#include <utility>

namespace Qx
{
namespace BinMapping
{

BinMapStreamLine::BinMapStreamLine(std::string &&aContent) noexcept
{
    mContent = std::move( aContent );
}

std::string BinMapStreamLine::ToString() const noexcept
{
    return mContent;
}

bool BinMapStreamLine::IsHeader() const noexcept
{
    const char lHeader[] = "test name";
    ( void ) lHeader;

    return {};
}

}
}
