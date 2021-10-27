/**
 * @file
 * @brief A shim of the z3 backend which exposes private members
 * \ingroup unittest
 */
#ifndef R_SHIM_Z3_HPP_
#define R_SHIM_Z3_HPP_

#include "testlib.hpp"


struct UnitTest::ClaricppUnitTest {
    /** A Shim of the Z3 backend which exposes private variables */
    struct ShimZ3 {
        /** The Z3 backend */
        Backend::Z3::Z3 bk {};
        /** Z3.convert */
        template <typename T> auto convert(const T b) { return bk.convert(b); }
        /** Z3.abstract */
        template <typename T> auto abstract(const T &b) { return bk.abstract(b); }
    };
};

#endif // R_SHIM_Z3_HPP_