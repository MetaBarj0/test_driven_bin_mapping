#ifndef BIN_MAP_STREAM_LINE_FIELDS_H
#define BIN_MAP_STREAM_LINE_FIELDS_H

namespace Qx
{
namespace BinMapping
{

template< typename... FieldTypes >
class BinMapStreamLineFields;

template< typename FirstFieldType, typename... RemainingFieldTypes >
class BinMapStreamLineFields< FirstFieldType, RemainingFieldTypes... >
{
public :
    bool IsEmpty() const noexcept { return true; }
};

}
}

#endif // BIN_MAP_STREAM_LINE_FIELDS_H
