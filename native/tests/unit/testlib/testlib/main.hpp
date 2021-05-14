/**
 * @file
 * @brief This file defines a macro to create a test and run it
 * Note: this macro defines the main() function
 * \ingroup testlib
 */
#ifndef R_UNIT_TESTLIB_TESTLIB_MAIN_HPP_
#define R_UNIT_TESTLIB_TESTLIB_MAIN_HPP_

#include "test_func.hpp"


/** Define the main function and use it to test a given function */
#define UNITTEST_DEFINE_MAIN_TEST(TFUNC)                                                          \
    /** Main function: test TFUNC */                                                              \
    int main() {                                                                                  \
        using namespace UnitTest::TestLib;                                                        \
        return test_func((TFUNC));                                                                \
    }


#endif
