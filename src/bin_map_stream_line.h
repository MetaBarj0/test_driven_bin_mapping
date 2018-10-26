#ifndef BIN_MAP_STREAM_LINE_H
#define BIN_MAP_STREAM_LINE_H

#include <string>

namespace Qx
{
namespace BinMapping
{

class BinMapStreamLine
{
public :
    BinMapStreamLine() = default;
    BinMapStreamLine( std::string &&aContent ) noexcept;

    std::string ToString() const noexcept;
    bool IsHeader() const noexcept;

private :
    std::string mContent;
};

}
}


#endif // BIN_MAP_STREAM_LINE_H