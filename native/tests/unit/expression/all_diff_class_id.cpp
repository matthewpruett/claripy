/** @file */

#include "testlib.hpp"

#include <set>


// For brevity
using namespace AST;
using namespace UnitTest::TestLib;


/** Each construction should have a unique pointer */
int all_diff_class_id() {

    const auto a1 = construct_ast<BV>();
    const auto a2 = construct_ast<FP>();
    const auto a3 = construct_ast<VS>();
    const auto a4 = construct_ast<Bool>();
    const auto a5 = construct_ast<String>();

    std::set<Constants::Int> ids;
    ids.insert(a1->class_id());
    ids.insert(a2->class_id());
    ids.insert(a3->class_id());
    ids.insert(a4->class_id());
    ids.insert(a5->class_id());

    UNITTEST_ASSERT(ids.size() == 5)
    return 0;
}