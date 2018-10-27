#ifndef STRING_MANIPULATIONS_H
#define STRING_MANIPULATIONS_H

#include <type_traits>
#include <locale>

namespace Qx
{

template< typename CharType,
          typename = std::enable_if_t< std::is_same< CharType, char >::value ||
                                       std::is_same< CharType, wchar_t >::value ||
                                       std::is_same< CharType, char16_t >::value ||
                                       std::is_same< CharType, char32_t >::value > >
struct ci_char_traits : public std::char_traits< CharType >
{
    static bool eq( CharType a, CharType b )
    noexcept( noexcept( std::tolower( std::declval< CharType >(), std::declval< std::locale >() ) ) )
    { return std::tolower( a, std::locale{} ) == std::tolower( b, std::locale{} ); }

    static bool lt( CharType a, CharType b )
    noexcept( noexcept( std::tolower( std::declval< CharType >(), std::declval< std::locale >() ) ) )
    { return std::tolower( a, std::locale{} ) < std::tolower( b, std::locale{} ); }

    static int compare( const CharType *s1, const CharType *s2, std::size_t n )
    noexcept( noexcept ( lt( std::declval< CharType >(), std::declval< CharType >() ) ) )
    {
        while ( n-- != 0 )
        {
            if ( lt( *s1, *s2 ) ) return -1;
            if ( lt( *s2, *s1 ) ) return 1;
            ++s1; ++s2;
        }

        return 0;
    }

    static const CharType * find( const CharType *s, int n, CharType a )
    noexcept( noexcept( std::tolower( std::declval< CharType >(), std::declval< std::locale >() ) ) )
    {
        const CharType l = std::tolower( a, std::locale{} );

        while ( n-- != 0 )
        {
            if ( std::tolower( *s, std::locale{} ) == l )
                return s;
            s++;
        }

        return nullptr;
    }
};

template< typename CharType,
          typename CharTraits = ci_char_traits< CharType >,
          typename Allocator = std::allocator< CharType > >
using basic_ci_string = std::basic_string< CharType, CharTraits, Allocator >;

using CIString = basic_ci_string< char >;

template< typename String, typename CharType, std::size_t N >
static bool StringStartsWith( const String &, const CharType ( & )[ N ] ) noexcept;


template< typename CharType, typename CharTraits, typename Allocator, std::size_t N >
static bool StringStartsWith( const std::basic_string< CharType, CharTraits, Allocator > &aString,
                              const CharType ( &aBuffer )[ N ] ) noexcept
{
    if( aString.size() < N - 1 )
        return false;

    for( std::size_t i = 0; i < N - 1; ++i )
        if( ! CharTraits::eq( aString[ i ], aBuffer[ i ] ) )
            return false;

    return true;
}

template< typename CharType, typename CharTraits, typename AllocatorReference, typename AllocatorPattern >
static bool StringStartsWith( const std::basic_string< CharType, CharTraits, AllocatorReference > &aReferenceString,
                              const std::basic_string< CharType, CharTraits, AllocatorPattern > &aPatternString ) noexcept
{
    if( aReferenceString.size() < aPatternString.size() )
        return false;

    std::size_t i = 0;
    for( CharType lChar : aPatternString )
        if( ! CharTraits::eq( lChar, aReferenceString[ i++ ] ) )
            return false;

    return true;
}

}

#endif // STRING_MANIPULATIONS_H
