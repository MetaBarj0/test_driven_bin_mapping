#ifndef TDD_KATA_BIN_MAPPING_H
#define TDD_KATA_BIN_MAPPING_H

#include <QtGlobal>

#if defined( TDD_KATA_BIN_MAPPING_SHARED )
#define TDD_KATA_BIN_MAPPING_API Q_DECL_EXPORT
#else
#define TDD_KATA_BIN_MAPPING_API Q_DECL_IMPORT
#endif

#endif // TDD_KATA_BIN_MAPPING_H