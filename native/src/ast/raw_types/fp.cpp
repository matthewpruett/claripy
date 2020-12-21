/** @file */
#include "fp.hpp"

#include "../../utils/inc.hpp"


// Define required AST functions
AST_RAWTYPES_DEFINE_AST_SUBBITS_ID_FUNCTIONS(FP)


// For brevity
using namespace AST;


/** @todo */
RawTypes::FP::FP(const Hash h, const Ops::Operation o) : RawTypes::Bits(h, o, 0) {}

#include <iostream>
/** @todo make this actually work */
Hash RawTypes::FP::hash(const Ops::Operation o) {
    std::cout << "fp: " << Hash(FP::static_class_id) * Hash(o) << std::endl;
    return Hash(FP::static_class_id) * (1 + Hash(o));
}
