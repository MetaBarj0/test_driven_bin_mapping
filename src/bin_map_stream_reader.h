#ifndef BIN_MAP_STREAM_READER_H
#define BIN_MAP_STREAM_READER_H

#include <iosfwd>
#include <memory>

#include "readable_binmap_content.h"
#include "common/exceptions.h"

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

private :
    bool IsReadyInternal() const
    {
        return ( mStream->good() && ( mStream->peek() != InputStream::traits_type::eof() ) );
    }

private :
    std::unique_ptr< InputStream > mStream;
};

}
}

#endif // BIN_MAP_STREAM_READER_H