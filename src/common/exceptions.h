#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace Qx
{
namespace BinMapping
{

class BadFilePath : public std::exception {};

}
}

#endif // EXCEPTIONS_H
