/**
 * @file
 * \ingroup testlib
 * @brief This defines a UnitTest error and wrapping macros
 */
#ifndef R_UNIT_TESTLIB_TESTLIB_FACTORIES_HPP_
#define R_UNIT_TESTLIB_TESTLIB_FACTORIES_HPP_

#include "annotation.hpp"
#include "expression.hpp"
#include "factory.hpp"
#include "op.hpp"
#include "utils.hpp"


namespace UnitTest::TestLib::Factories {

    /** Create a simple Symbol */
    inline auto symbol(std::string name = std::string { "hi" }) { Op::factory<Op::Symbol>(name); }

    /** Create a simple Literal */
    inline Op::BasePtr literal(const Constants::Int i = 0) {
        const constexpr Constants::UInt size { sizeof(Constants::Int) };
        char buf[size]; // NOLINT
        std::memcpy(buf, &i, size);
        return Op::factory<Op::Literal>(std::string { buf, size });
    }

    /** Make it easier to create expressions */
    template <typename T = Expression::Bool>
    Expression::BasePtr t_literal(const Constants::Int i = 0) {
        static_assert(std::is_base_of_v<Expression::Base, T>,
                      "T must derive from Expression::Base");
        auto ans { std::vector<Factory::Ptr<Annotation::Base>> {} };
        auto op { literal(i) };
        auto baseop { Utils::up_cast<Op::Base>(op) };
        if constexpr (std::is_base_of_v<Expression::Bits, T>) {
            return Expression::factory<T>(std::move(ans), false, std::move(baseop),
                                          Utils::static_down_cast<Op::Literal>(op)->bit_length());
        }
        else {
            return Expression::factory<T>(std::move(ans), false, std::move(baseop));
        }
    }

} // namespace UnitTest::TestLib::Factories

#endif
