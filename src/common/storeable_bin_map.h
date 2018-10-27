#ifndef STOREABLE_BIN_MAP_H
#define STOREABLE_BIN_MAP_H

#include "common/string_manipulations.h"

namespace Qx
{
namespace BinMapping
{

struct StoreableBinMap
{
    virtual ~StoreableBinMap() = default;

    virtual Qx::CIString GetHeaderLineStart() const noexcept = 0;
    virtual char GetFieldDelimiter() const noexcept = 0;
    virtual char GetEndOfLine() const noexcept = 0;
    virtual void SetHeaderLineDetectedToggle() noexcept = 0;
    virtual bool IsHeaderLineDetected() const noexcept = 0;
};

}
}


#endif // STOREABLE_BIN_MAP_H