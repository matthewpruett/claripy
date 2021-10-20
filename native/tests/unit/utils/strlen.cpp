/**
 * @file
 * \ingroup unittest
 */
#include "testlib.hpp"

#include <cstring>


/** Verify the file line hash macros work */
void strlen() {
    constexpr CCSC msg { "This is a test" };
    const constexpr auto n { Utils::strlen(msg) };
    UNITTEST_ASSERT(n == std::strlen(msg));
}

// Define the test
UNITTEST_DEFINE_MAIN_TEST(strlen)
