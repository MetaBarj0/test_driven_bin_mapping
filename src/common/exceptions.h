#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace Qx
{
namespace BinMapping
{

class InvalidStream: public std::exception {};
class OutOfRangeFieldIndex : public std::exception {};

}
}

#endif // EXCEPTIONS_H
