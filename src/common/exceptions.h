#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "tdd_kata_bin_mapping.h"

#include <exception>

namespace Qx
{
namespace BinMapping
{

class TDD_KATA_BIN_MAPPING_API InvalidStream: public std::exception {};
class TDD_KATA_BIN_MAPPING_API OutOfRangeFieldIndex : public std::exception {};
class TDD_KATA_BIN_MAPPING_API BinMapItemNotFound : public std::exception {};

}
}

#endif // EXCEPTIONS_H
