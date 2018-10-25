#ifndef READABLE_BINMAP_CONTENT_H
#define READABLE_BINMAP_CONTENT_H

namespace Qx
{
namespace BinMapping
{

struct ReadableBinMapContent
{
public :
    virtual ~ReadableBinMapContent() = default;

    virtual bool IsOpen() const noexcept = 0;
};

}
}

#endif // READABLE_BINMAP_CONTENT_H
