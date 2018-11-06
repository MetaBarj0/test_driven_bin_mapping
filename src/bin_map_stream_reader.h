#ifndef BIN_MAP_STREAM_READER_H
#define BIN_MAP_STREAM_READER_H

#include "readable_binmap_content.h"
#include "common/exceptions.h"
#include "bin_map_stream_line.h"
#include "common/storeable_bin_map.h"
#include "common/string_manipulations.h"

#include <iosfwd>
#include <memory>
#include <string>

namespace Qx
{
namespace BinMapping
{

template< typename InputStream >
class BinMapStreamReader : public ReadableBinMapContent
{
public :
    BinMapStreamReader( InputStream &&aStream )
    {
        mStream.reset( new InputStream( std::move( aStream ) ) );

        if( ! IsReadyInternal() )
            throw InvalidStream{};
    }

    bool IsReady() const noexcept override { return IsReadyInternal(); }

    BinMapStreamLine GetLineFor( StoreableBinMap &aStoreable ) const noexcept
    {
        std::string lLine;
        bool lResult = static_cast< bool >( std::getline( *mStream, lLine, aStoreable.GetEndOfLine() ) );

        if( lResult )
            return BinMapStreamLine{ lLine, GetLineKind( lLine, aStoreable ) };

        return {};
    }

private :
    bool IsReadyInternal() const
    {
        return ( mStream->good() && ( mStream->peek() != InputStream::traits_type::eof() ) );
    }

    bool IsCommentLine( const std::string &aLine, StoreableBinMap &aStoreable ) const
    {
        const auto lTrimmedOfSpacesString = TrimStringLeftSideOf( aLine, ' ' );

        return StringStartsWith( lTrimmedOfSpacesString, aStoreable.GetCommentLineStart() );
    }

    bool IsProcessedHeaderLine( const std::string &aLine, StoreableBinMap &aStoreable ) const
    {
        bool lIsHeader = false;
        if( ! aStoreable.IsHeaderLineDetected() )
            lIsHeader = StringStartsWith( Qx::CIString{ aLine.c_str() }, aStoreable.GetHeaderLineStart() );

        if( lIsHeader )
            aStoreable.SetHeaderLineDetectedToggle();

        return lIsHeader;
    }

    BinMapStreamLineKinds GetLineKind( const std::string &aLine, StoreableBinMap &aStoreable ) const
    {
        if( IsCommentLine( aLine, aStoreable ) )
            return BinMapStreamLineKinds::comment;

        if( IsProcessedHeaderLine( aLine, aStoreable ) )
            return BinMapStreamLineKinds::header;

        return BinMapStreamLineKinds::unspecified;
    }

private :
    std::unique_ptr< InputStream > mStream;
};

}
}

#endif // BIN_MAP_STREAM_READER_H