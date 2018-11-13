#include "lvm_wt_bin_map_store.h"
#include "lvm_wt_bin_map_item.h"
#include "common/exceptions.h"
#include "lvm_wt_exceptions.h"
#include "bin_map_stream_reader.h"
#include "common/string_manipulations.h"

#include <memory>
#include <algorithm>

namespace Qx
{
namespace BinMapping
{

LvmWtBinMapStore::LvmWtBinMapStore( std::unique_ptr< ReadableBinMapContent > &&aBinMapFileReader ) :
    mFileReader{ std::move( aBinMapFileReader ) }
{
    if( ! mFileReader->IsReady() )
        throw InvalidStream{};

    BinMapStreamLine aLine = mFileReader->GetLineFor( *this );

    while( ! aLine.IsEmpty() )
    {
        if( aLine.IsHeader() || aLine.IsComment() )
        {
            aLine = mFileReader->GetLineFor( *this );
            continue;
        }

        const auto &lFields = aLine.ToFields< std::string, int, int, std::string >( *this );

        if( ! lFields.IsValid() )
            throw InvalidStream{};

        mItems.emplace_back( lFields.GetValueAt< LvmWtBinMapItem::test_name_field >(),
                             lFields.GetValueAt< LvmWtBinMapItem::test_number_field >(),
                             lFields.GetValueAt< LvmWtBinMapItem::bin_number_field >(),
                             lFields.GetValueAt< LvmWtBinMapItem::bin_name_field >() );

        aLine = mFileReader->GetLineFor( *this );
    }
}

LvmWtBinMapItem LvmWtBinMapStore::GetBinMapItemByKey(int aKey) const
{
    auto lIterator = std::find_if( std::cbegin( mItems ), std::cend( mItems ),
                                   [ aKey ]( const LvmWtBinMapItem &aItem ){ return aItem.GetTestNumber() == aKey; } );

    if( lIterator == std::cend( mItems ) )
        throw BinMapItemNotFound{};

    return *lIterator;
}

bool LvmWtBinMapStore::IsEmpty() const noexcept
{
    return mItems.empty();
}

Qx::CIString LvmWtBinMapStore::GetHeaderLineStart() const noexcept
{
    return { "test name" };
}

char LvmWtBinMapStore::GetCommentLineStart() const noexcept
{
    return '#';
}

char LvmWtBinMapStore::GetFieldDelimiter() const noexcept
{
    return ',';
}

char LvmWtBinMapStore::GetEndOfLine() const noexcept
{
    return '\n';
}

void LvmWtBinMapStore::SetHeaderLineDetectedToggle() noexcept
{
    mIsHeaderLineDetected = true;
}

bool LvmWtBinMapStore::IsHeaderLineDetected() const noexcept
{
    return  mIsHeaderLineDetected;
}

}
}