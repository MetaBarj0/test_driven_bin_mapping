#ifndef BIN_MAP_STREAM_LINE_FIELDS_H
#define BIN_MAP_STREAM_LINE_FIELDS_H

#include "common/storeable_bin_map.h"
#include <string>
#include <algorithm>
#include <sstream>

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
    BinMapStreamLineFields( const StoreableBinMap &, const std::string & ) {}

    bool IsEmpty() const noexcept { return true; }
};

template< typename LastFieldType >
class BinMapStreamLineFields< LastFieldType >
{
public :
    BinMapStreamLineFields( const StoreableBinMap &, const std::string &aLine ) :
        mField{ {}, false }
    {
        std::stringstream lStream;
        lStream << aLine;
        lStream >> mField.first;

        mField.second = static_cast< bool >( lStream );
    }

    bool IsEmpty() const noexcept { return ! mField.second; }

private :
    std::string RemoveFirstFieldFromString( const std::string &aLine ) const noexcept { return aLine; }

private :
    std::pair< LastFieldType, bool > mField;
};

}
}

#endif // BIN_MAP_STREAM_LINE_FIELDS_H
