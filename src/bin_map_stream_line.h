#ifndef BIN_MAP_STREAM_LINE_H
#define BIN_MAP_STREAM_LINE_H

#include <string>

namespace Qx
{
namespace BinMapping
{

enum class BinMapStreamLineKinds
{
    header,
    comment,
    fields,
    unspecified
};

class BinMapStreamLine
{
public :
    BinMapStreamLine() = default;
    BinMapStreamLine( const std::string &aContent, BinMapStreamLineKinds aKind ) noexcept;

    std::string ToString() const noexcept;
    bool IsHeader() const noexcept;
    bool IsComment() const noexcept;

private :
    std::string mContent;
    BinMapStreamLineKinds mKind = BinMapStreamLineKinds::unspecified;
};

}
}


#endif // BIN_MAP_STREAM_LINE_H