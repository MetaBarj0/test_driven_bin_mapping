#ifndef READABLE_BINMAP_CONTENT_H
#define READABLE_BINMAP_CONTENT_H

namespace Qx
{
namespace BinMapping
{

class BinMapStreamLine;
struct StoreableBinMap;

struct ReadableBinMapContent
{
public :
    virtual ~ReadableBinMapContent() = default;

    virtual bool IsReady() const noexcept = 0;
    virtual BinMapStreamLine GetLineFor( StoreableBinMap &aStoreable ) const noexcept = 0;
};

}
}

#endif // READABLE_BINMAP_CONTENT_H
