#ifndef BIN_MAP_STREAM_LINE_H
#define BIN_MAP_STREAM_LINE_H

#include "bin_map_stream_line_fields.h"

#include <string>

namespace Qx
{
namespace BinMapping
{

struct StoreableBinMap;

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
    BinMapStreamLine(const std::string &aContent, BinMapStreamLineKinds aKind ) noexcept;

    std::string ToString() const noexcept;
    bool IsHeader() const noexcept;
    bool IsComment() const noexcept;

    template< typename... FieldTypes >
    auto ToFields( const StoreableBinMap &aStore ) const noexcept
    {
        return BinMapStreamLineFields< FieldTypes... >{ aStore, mContent };
    }

private :
    std::string mContent;
    BinMapStreamLineKinds mKind = BinMapStreamLineKinds::unspecified;
};

}
}


#endif // BIN_MAP_STREAM_LINE_H