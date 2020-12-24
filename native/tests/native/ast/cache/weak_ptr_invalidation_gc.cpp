/** @file */

#include "src/ast/base.hpp"
#include "src/ast/factory.hpp"
#include "src/ops/operations_enum.hpp"

#include <set>


// For brevity
using namespace AST;


namespace Tests::Native {
    /** A struct used to give friend access to unittests */
    struct ClaricppUnitTest {
        /** Get the cache size */
        decltype(AST::Private::factory_cache)::CacheMap::size_type size() {
            return AST::Private::factory_cache.cache.size();
        }
        /** Passthrough unsafe_gc */
        void unsafe_gc() { return AST::Private::factory_cache.unsafe_gc(); }
    };
} // namespace Tests::Native


/** Construct a Base */
template <typename T> T construct() {
    std::set<BackendID> s;
    return factory<T>(std::move(s), std::move((Ops::Operation) 0));
}


/** Ensure weak_ptrs are properly invalidated and removed by both gc and find */
int weak_ptr_invalidation_gc() {
    Tests::Native::ClaricppUnitTest cache;

    // Create and destroy a base
    { Base a = construct<Base>(); }

    // Check cache size
    if (cache.size() != 1) {
        return 1;
    }

    // Garbage collect then verify size
    cache.unsafe_gc();
    return cache.size();
}