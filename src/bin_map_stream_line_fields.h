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
class BinMapStreamLineFields< FirstFieldType, RemainingFieldTypes... > :
    public BinMapStreamLineFields< RemainingFieldTypes... >
{
public :
    BinMapStreamLineFields( const StoreableBinMap &aStore, const std::string &aLine ) :
        BinMapStreamLineFields<RemainingFieldTypes...>{ aStore, GetLineForNextField( aStore, aLine ) },
        mField{ {}, false }
    {
        const auto lDelimiter = aStore.GetFieldDelimiter();
        auto lIterator = std::find_if( std::cbegin( aLine ),
                                       std::cend( aLine ),
                                       [ lDelimiter ]( char aChar ) { return aChar == lDelimiter; } );

        if( lIterator != std::cend( aLine ) )
        {
            std::stringstream lStream;
            lStream << std::string{ std::cbegin( aLine ), lIterator };
            lStream >> mField.first;

            mField.second = static_cast< bool >( lStream );
        }

    }

    bool IsEmpty() const noexcept { return ! mField.second; }

private :
    auto GetLineForNextField( const StoreableBinMap &aStore, const std::string &aLine ) const
    {
        const auto lDelimiter = aStore.GetFieldDelimiter();
        auto lIterator = std::find_if( std::cbegin( aLine ),
                                       std::cend( aLine ),
                                       [ lDelimiter ]( char aChar ) { return aChar == lDelimiter; } );
        if( lIterator != std::cend( aLine ) )
            ++lIterator;

        return std::string{ lIterator, std::cend( aLine ) };
    }

private :
    std::pair< FirstFieldType, bool > mField;
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
