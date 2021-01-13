/** @file */
#include "expression.hpp"
#include "testlib.hpp"

#include <set>


// For brevity
using namespace Expression;
using namespace UnitTest::TestLib;


/** Down casting should fail */
int down_cast() {
    ConcreteIntLiteral a = literal_int();
    Base b = up_cast<Base>(a);
    Bool c = down_cast<Bool>(b);
    UNITTEST_ASSERT(c == nullptr)
    return 0;
}