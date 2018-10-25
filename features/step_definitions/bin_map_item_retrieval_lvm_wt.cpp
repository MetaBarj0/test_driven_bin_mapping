#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>

#include "lvm_wt_bin_map_store.h"
#include "lvm_wt_bin_map_item.h"

#include <string>
#include <memory>
#include <fstream>

using cucumber::ScenarioScope;

struct Context
{
    std::string mFilePath;
    bool mFileExists = false;
    std::unique_ptr< Qx::BinMapping::LvmWtBinMapStore> mBinMapStore;
    std::unique_ptr< Qx::BinMapping::LvmWtBinMapItem > mRetrievedBinMapItem;
};

GIVEN( "^the file (.+)$" )
{
    REGEX_PARAM( std::string, lFilePath );
    ScenarioScope< Context > lContext;
    lContext->mFilePath = std::move( lFilePath );
}

WHEN( "^I check the file exists$" )
{
    ScenarioScope< Context > lContext;
    std::ifstream lFileStream{ lContext->mFilePath };
    lContext->mFileExists = static_cast< bool >( lFileStream );
}

THEN( "^the specified file should be reported as existing$" )
{
    ScenarioScope< Context > lContext;
    ASSERT_TRUE( lContext->mFileExists );
}

GIVEN( "^an existing file (.+)$" )
{
    REGEX_PARAM( std::string, lFilePath );
    ScenarioScope< Context > lContext;

    lContext->mFilePath = std::move( lFilePath );
    lContext->mFileExists = true;
}

WHEN( "^I create a bin map store from that file$" )
{
    ScenarioScope< Context > lContext;

    lContext->mBinMapStore.reset( new Qx::BinMapping::LvmWtBinMapStore{ lContext->mFilePath } );
}

THEN( "^the bin map store should have been created succesfully$" )
{
    ScenarioScope< Context > lContext;

    ASSERT_TRUE( lContext->mBinMapStore );
}

GIVEN( "^a bin map item store created from an existing file (.+)$" )
{
    REGEX_PARAM( std::string, lFilePath );
    ScenarioScope< Context > lContext;

    lContext->mFilePath = std::move( lFilePath );
    lContext->mFileExists = true;
    lContext->mBinMapStore.reset( new Qx::BinMapping::LvmWtBinMapStore{ lContext->mFilePath } );
}

WHEN( "^I query a bin map item using the key (\\d+)$" )
{
    REGEX_PARAM( int, lKey );
    ScenarioScope< Context > lContext;

    try
    {
        auto &&lBinMapItem = lContext->mBinMapStore->GetBinMapItemByKey( lKey );
        lContext->mRetrievedBinMapItem.reset( new Qx::BinMapping::LvmWtBinMapItem{ std::move( lBinMapItem ) } );
    }
    catch ( ... )
    {
    }
}

THEN( "^the bin map item should have been retrieved successfully$" )
{
    ScenarioScope< Context > lContext;

    ASSERT_TRUE( lContext->mRetrievedBinMapItem );
}

AND( "^the test name should be (.+)$" )
{
    REGEX_PARAM( std::string, lTestName );
    ScenarioScope< Context > lContext;

    ASSERT_STRCASEEQ( lTestName.c_str(), lContext->mRetrievedBinMapItem->GetTestName().c_str() );
}

AND( "^the binning number should be (.+)$" )
{
    REGEX_PARAM( int, lBinNumber );
    ScenarioScope< Context > lContext;

    ASSERT_EQ( lBinNumber, lContext->mRetrievedBinMapItem->GetBinNumber() );
}

AND( "^the binning name should be (.+)$" )
{
    REGEX_PARAM( std::string, lBinName );
    ScenarioScope< Context > lContext;

    ASSERT_STRCASEEQ( lBinName.c_str(), lContext->mRetrievedBinMapItem->GetBinName().c_str() );
}