/**
 * @file
 * \ingroup unittest
 */
#include "testlib.hpp"

#include <set>


// For brevity
using namespace Expression;
using namespace UnitTest::TestLib;


/** A struct used to give friend access to unittests */
struct UnitTest::ClaricppUnitTest {
    /** Get the cache size */
    decltype(Expression::Private::cache)::CacheMap::size_type size() {
        return Expression::Private::cache.cache.size();
    }
    /** Passthrough unsafe_gc */
    void unsafe_gc() { return Expression::Private::cache.unsafe_gc(); }
};


/** Ensure weak_ptrs are properly invalidated and removed by both gc and find */
void weak_ptr_invalidation_gc() {
    UnitTest::ClaricppUnitTest cache;

    // Create and destroy a base
    { (void) literal_int(); }

    // Check cache size
    UNITTEST_ASSERT(cache.size() == 1)

    // Garbage collect then verify size
    cache.unsafe_gc();
    UNITTEST_ASSERT(cache.size() == 0)
}

// Define the test
UNITTEST_DEFINE_MAIN_TEST(weak_ptr_invalidation_gc)
