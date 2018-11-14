#ifndef BIN_MAP_STREAM_LINE_FIELDS_H
#define BIN_MAP_STREAM_LINE_FIELDS_H

#include "common/storeable_bin_map.h"
#include "common/exceptions.h"

#include <string>
#include <algorithm>
#include <sstream>

namespace Qx
{
namespace BinMapping
{

namespace details
{

template< std::size_t FieldIndex, typename BinMapStreamLineFields >
struct BinMapStreamLineFieldsValueExtractor
{
    constexpr BinMapStreamLineFieldsValueExtractor( const BinMapStreamLineFields &aFields ) noexcept :
        mFields{ aFields } {}

    constexpr auto operator ()() const noexcept
    {
        using BinMapStreamLineFieldsBaseConstReference = decltype( std::declval< BinMapStreamLineFields >().GetBase() );
        using BinMapStreamLineFieldsBase =
            std::remove_const_t< std::remove_reference_t< BinMapStreamLineFieldsBaseConstReference > >;

        return BinMapStreamLineFieldsValueExtractor< FieldIndex - 1,
                                                     BinMapStreamLineFieldsBase >{ mFields.GetBase() }();
    }

    const BinMapStreamLineFields &mFields;
};

template< typename BinMapStreamLineFields >
struct BinMapStreamLineFieldsValueExtractor< 0u, BinMapStreamLineFields >
{
    constexpr BinMapStreamLineFieldsValueExtractor( const BinMapStreamLineFields &aFields ) noexcept :
        mFields{ aFields } {}

    auto operator ()() const noexcept
    { return mFields.GetCurrent().mField.first; }

    const BinMapStreamLineFields &mFields;
};

}

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

    bool IsValid() const noexcept
    { return BinMapStreamLineFields< RemainingFieldTypes... >::IsValid() && mField.second; }

    template< std::size_t FieldIndex >
    auto GetValueAt() const
    { return details::BinMapStreamLineFieldsValueExtractor< FieldIndex, BinMapStreamLineFields >{ *this }(); }

protected :
    using BinMapStreamLineFields< RemainingFieldTypes... >::GetNextDelimiterIterator;
    using BinMapStreamLineFields< RemainingFieldTypes... >::AssignStringToField;

    template< std::size_t, typename >
    friend struct details::BinMapStreamLineFieldsValueExtractor;

    const auto & GetBase() const noexcept
    { return BinMapStreamLineFields< RemainingFieldTypes... >::GetCurrent(); }

    const auto & GetCurrent() const noexcept
    { return *this; }

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

    bool IsValid() const noexcept { return mField.second; }

    template< std::size_t aFieldIndex >
    const auto & GetValueAt() const
    {
        if( aFieldIndex > 0 )
            throw OutOfRangeFieldIndex{};

        return mField.first;
    }

private :
    template< typename FieldType >
    struct FieldAssigner
    {
        static void AssignStringToField( const std::string &aString, std::pair< FieldType, bool > &aField )
        {
            std::stringstream lStream;
            lStream << std::boolalpha;
            lStream << aString;
            lStream >> aField.first;

            aField.second = static_cast< bool >( lStream );
        }
    };

    template< typename CharType, typename CharTraits, typename Allocator >
    struct FieldAssigner< std::basic_string< CharType, CharTraits, Allocator > >
    {
        using StringType = std::basic_string< CharType, CharTraits, Allocator >;

        static void AssignStringToField( const std::string &aString, std::pair< StringType, bool > &aField )
        {
            aField.first = aString;
            aField.second = true;
        }
    };

protected :
    auto GetNextDelimiterIterator( const StoreableBinMap &aStore, const std::string &aLine ) const noexcept
    {
        return std::find_if( std::cbegin( aLine ),
                             std::cend( aLine ),
                             [ &aStore ]( char aChar ) { return aChar == aStore.GetFieldDelimiter(); } );
    }

    template< typename FieldType >
    static void AssignStringToField( const std::string &aString, std::pair< FieldType, bool >& aField )
    { FieldAssigner< FieldType >::AssignStringToField( aString, aField ); }

    template< std::size_t, typename >
    friend struct details::BinMapStreamLineFieldsValueExtractor;

    const auto & GetCurrent() const noexcept
    { return *this; }

private :
    std::pair< LastFieldType, bool > mField;
};

}
}

#endif // BIN_MAP_STREAM_LINE_FIELDS_H
