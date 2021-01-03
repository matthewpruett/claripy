/** @file */

#include "testlib.hpp"

#include <set>


// For brevity
using namespace AST;
using namespace UnitTest::TestLib;


/** Hashing must take into account type differences */
int identical_bool_int() {
    Bool a = construct_ast<Bool>();
    Int b = construct_ast<Int>();
    Base a2 = up_cast<Base>(a);
    Base b2 = up_cast<Base>(b);
    UNITTEST_ASSERT(a2 != b2);
    return 0;
}