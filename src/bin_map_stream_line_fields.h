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
        auto lIterator = GetNextDelimiterIterator( aStore, aLine );

        if( lIterator != std::cend( aLine ) )
            AssignStringToField( std::string{ std::cbegin( aLine ), lIterator }, mField );
    }

    bool IsEmpty() const noexcept
    { return BinMapStreamLineFields< RemainingFieldTypes... >::IsEmpty() || ! mField.second; }

protected :
    using BinMapStreamLineFields< RemainingFieldTypes... >::GetNextDelimiterIterator;
    using BinMapStreamLineFields< RemainingFieldTypes... >::AssignStringToField;

private :
    auto GetLineForNextField( const StoreableBinMap &aStore, const std::string &aLine ) const
    {
        auto lIterator = GetNextDelimiterIterator( aStore, aLine );

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
    BinMapStreamLineFields( const StoreableBinMap &aStore, const std::string &aLine ) :
        mField{ {}, false }
    {
        auto lIterator = GetNextDelimiterIterator( aStore, aLine );

        if( lIterator == std::cend( aLine ) )
            AssignStringToField( aLine, mField );
    }

    bool IsEmpty() const noexcept { return ! mField.second; }

    const LastFieldType & operator []( std::size_t ) const
    {
        return mField.first;
    }

protected :
    auto GetNextDelimiterIterator( const StoreableBinMap &aStore, const std::string &aLine ) const noexcept
    {
        return std::find_if( std::cbegin( aLine ),
                             std::cend( aLine ),
                             [ &aStore ]( char aChar ) { return aChar == aStore.GetFieldDelimiter(); } );
    }

    template< typename FieldType >
    static void AssignStringToField( const std::string &aString, std::pair< FieldType, bool >& aField ) noexcept
    {
        std::stringstream lStream;
        lStream << std::boolalpha;
        lStream << aString;
        lStream >> aField.first;

        aField.second = static_cast< bool >( lStream );
    }

private :
    std::pair< LastFieldType, bool > mField;
};

}
}

#endif // BIN_MAP_STREAM_LINE_FIELDS_H
