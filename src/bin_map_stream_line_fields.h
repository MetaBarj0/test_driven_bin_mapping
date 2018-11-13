/**
 * The code in this file is the most complex of the library. It uses some tricks of meta-programming and heavily uses
 * templates. Beyond that, the code is fully tested.
 *
 * I documented each class in order you understand the role of each in field value extraction from a bin map stream.
 *
 * First, why these class are designed using template and meta programming? Well, specifications about bin map format
 * specified that fields of a line has fixed format. Thus, I designed the class BinMapStreamLineFields to be a template
 * parameterized by the type of fields. For instance :
 *
 *   GS SHORT,5,29,GS SHORT
 *
 * is a stream line having 4 fields of type string, integer, integer and string.
 * Therefore, an instance of the BinMapStreamLine template class corresponding to this line could be :
 *
 *   BinMapStreamLineFields< std::string, int, int, std::string >
 *
 * c++11 offers us variadic templates, allowing us to define template without having to know in advance how much
 * parameter a template takes. That is a great tool, but it could be mind boggling as you could see later.
 *
 * Anyway, the main template of interest here is BinMapStreamLineFields.
 * BinMapStreamLineFieldsValueExtractor is an implementation details and an helper that is necessary because with
 * c++, you cannot define partial template specialization of member methods. The template member method I talk
 * about is BinMapStreamLineFields::GetValueAt<>.
 * Therefore, this is this method that uses BinMapStreamLineFieldsValueExtractor facilities.
 *
 * Please, read description of each class and methods to get the point about how it works, if the topic is of interest
 * for you.
 */

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

/**
 * In c++, it is common to define a 'details' namespace to gather implementation details not intended to be exposed to
 * the client.
 */
namespace details
{

/**
 * This class is the helper responsible of extracting a field value given an index within a BinmapStreamLineFields
 * class instance.
 *
 * This specialization match any index greater than 0 and recursively call the operator () to get the value at the
 * desired index.
 */
template< std::size_t FieldIndex, typename BinMapStreamLineFields >
struct BinMapStreamLineFieldsValueExtractor
{
    constexpr BinMapStreamLineFieldsValueExtractor( const BinMapStreamLineFields &aFields ) noexcept :
        mFields{ aFields } {}

    constexpr auto operator ()() const noexcept
    {
        /**
         * extracting types with using get the code more understandable
         */
        using BinMapStreamLineFieldsBaseConstReference = decltype( std::declval< BinMapStreamLineFields >().GetBase() );
        using BinMapStreamLineFieldsBase =
            std::remove_const_t< std::remove_reference_t< BinMapStreamLineFieldsBaseConstReference > >;

        /**
         * Recursion occurs here, construct a temporary BinmapStreamLineFieldsValueExtractor with the base of the
         * original BinMapStreamLineFields and the index substracted by 1
         */
        return BinMapStreamLineFieldsValueExtractor< FieldIndex - 1,
                                                     BinMapStreamLineFieldsBase >{ mFields.GetBase() }();
    }

    const BinMapStreamLineFields &mFields;
};

/**
 * This specialization matches when index of wanted field is 0. No recursion here, it just extracts the field of the
 * specified BinMapStreamLineFields reference.
 */
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

/**
 * This is the signature of the template class that represents all fields of a stream line.
 * This template version, or specialization is not defined here because it is constrianed later with other
 * specializations as you can see later.
 * The template parameter pack represents all types of each field in order.
 * For instance, for a stream line containing :
 *   GS SHORT, 5, 29, GS SHORT
 * the template
 *   BinMapStreamLineFields< std::string, int, int, std::string >
 * could correspond.
 *
 * Please, see below to get the point about how template specialization work
 */
template< typename... FieldTypes >
class BinMapStreamLineFields;

/**
 * This specialization matches for any template having 2 or more type as parameters.
 * As you can see, it inherits of itself as template but parameterized with all types but the first.
 * For instance, with a template parameterized as :
 *   BinMapStreamLineFields< int, bool, std::string >
 * it creates an inheritance layout ressembling to :
 *   BinMapStreamLineFields< int, bool, std::string >
 *   | int member
 *   | BinMapStreamLineFields< bool, std::string >
 *   | | bool member
 *   | | BinMapStreamLineFields< std::string >
 *   | | | std::string member
 * This class exposes besides a constructor and a status method a template method allowing one to access a field value
 * by an index decided at compile time, as wanted regarding specifications.
 */
template< typename FirstFieldType, typename... RemainingFieldTypes >
class BinMapStreamLineFields< FirstFieldType, RemainingFieldTypes... > :
    public BinMapStreamLineFields< RemainingFieldTypes... >
{
public :
    BinMapStreamLineFields( const StoreableBinMap &aStore, const std::string &aLine ) :
        BinMapStreamLineFields<RemainingFieldTypes...>{ aStore, GetLineForNextField( aStore, aLine ) },
        mField{ {}, false }
    {
        /**
         * In the initializer list, the base class is constrcuted using the store as well as a substring of the original
         * one. The first field is removed in the substring.
         * In the body, the field value is computed from the first field extracted from aLine.
         */

        auto lIterator = GetNextDelimiterIterator( aStore, aLine );

        if( lIterator != std::cend( aLine ) )
            AssignStringToField( std::string{ std::cbegin( aLine ), lIterator }, mField );
    }

    bool IsValid() const noexcept
    {
        /**
         * Status method.
         * Make sure all fields have been set all along the inheritance hierarchy.
         * As you can see, BinMapStreamLineFields< RemainingFieldTypes... > is the base class.
         */

        return BinMapStreamLineFields< RemainingFieldTypes... >::IsValid() || ! mField.second;
    }

    template< std::size_t FieldIndex >
    auto GetValueAt() const
    {
        /**
         * Most valuable method. This is a template. As c++ does not offer us the possibility to partially specialize a
         * template member function, this method relies on an helper that has the responsibility to provide the value of
         * a field targeted by an index.
         */

        return details::BinMapStreamLineFieldsValueExtractor< FieldIndex, BinMapStreamLineFields >{ *this }();
    }

protected :
    /**
     * using directive allowing to define methods existing in the base class without having to rewrite them.
     */
    using BinMapStreamLineFields< RemainingFieldTypes... >::GetNextDelimiterIterator;
    using BinMapStreamLineFields< RemainingFieldTypes... >::AssignStringToField;

    /**
     * Allow access of protected and private stuff for the helper responsible to extract a field value
     */
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
    /**
     * The field value per se. The second member of the pair indicates if the value has been initialized or not.
     */
    std::pair< FirstFieldType, bool > mField;
};

/**
 * This template specialization is the last one in the inheritance hierarchy. Therefore, this is the base class of any
 * BinMapStreamLineFields template having 2 or more type in its parameter list.
 *
 * Its implementation is much simpler as it is a peculiar case of fields (only one type)
 */
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

    bool IsValid() const noexcept { return ! mField.second; }

    template< std::size_t aFieldIndex >
    const auto & GetValueAt() const
    {
        if( aFieldIndex > 0 )
            throw OutOfRangeFieldIndex{};

        return mField.first;
    }

private :
    /**
     * The template below is another helper for the AssignStringToField method. It helps to translate a string to a
     * streamable type only if the streamable type is not a string itself.
     * It is necessary because putting a string containing space characters within splits that string and gives only a
     * substring before the first space encountered.
     */

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

    /**
     * The two next methods are peeked in derived class thanks to using declarations allowing me to define them only
     * once here, in the most base class of the inheritance hierarchy.
     */

protected :
    auto GetNextDelimiterIterator( const StoreableBinMap &aStore, const std::string &aLine ) const noexcept
    {
        return std::find_if( std::cbegin( aLine ),
                             std::cend( aLine ),
                             [ &aStore ]( char aChar ) { return aChar == aStore.GetFieldDelimiter(); } );
    }

    template< typename FieldType >
    static void AssignStringToField( const std::string &aString, std::pair< FieldType, bool >& aField )
    {
        FieldAssigner< FieldType >::AssignStringToField( aString, aField );
    }

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
