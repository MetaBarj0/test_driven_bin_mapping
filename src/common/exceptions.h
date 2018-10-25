#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace Qx
{
namespace BinMapping
{

class InvalidStream: public std::exception {};

}
}

#endif // EXCEPTIONS_H
