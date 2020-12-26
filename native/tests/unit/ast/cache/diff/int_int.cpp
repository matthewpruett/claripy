/** @file */

#include "src/ast/int.hpp"

#include "src/ast/factory.hpp"
#include "src/ops/operations_enum.hpp"

#include <set>

/** Construct an Int */
AST::Int construct(Ops::Operation o) {
    std::set<AST::BackendID> s;
    return AST::factory<AST::Int>(std::move(s), std::move(o));
}

/** Test creating an AST::Int */
int int_int() {
    AST::Int a = construct((Ops::Operation) 0);
    AST::Int b = construct((Ops::Operation) 1);
    if (a != b) {
        return 0;
    }
    else {
        return 1;
    }
}