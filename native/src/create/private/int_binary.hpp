/**
 * @file
 * @brief This file defines a method to create Expressions with standard binary ops
 */
#ifndef __CREATE_PRIVATE_INTBINARY_HPP__
#define __CREATE_PRIVATE_INTBINARY_HPP__

#include "bit_length.hpp"
#include "size_mode.hpp"

#include "../constants.hpp"


namespace Create::Private {

    /** Create a Expression with an int binary op */
    template <typename IntT, typename Out, typename In, typename OpT, SizeMode Mode,
              typename... Allowed>
    inline EBasePtr int_binary(EAnVec &&av, const EBasePtr &expr, const IntT integer) {
        static_assert(Utils::qualified_is_in<IntT, Constants::UInt, Constants::Int>,
                      "Create::Private::int_binary requires IntT be either Constants::UInt or "
                      "Constants::Int");
        static_assert(Utils::is_ancestor<Expression::Base, Out>,
                      "Create::Private::int_binary requires Out be an Expression");
        static_assert(Utils::is_ancestor<Expression::Base, In>,
                      "Create::Private::int_binary requires In be an Expression");
        static_assert(Op::is_int_binary<OpT>,
                      "Create::Private::int_binary requires a int binary OpT");
        if constexpr (Utils::is_ancestor<Expression::Bits, Out>) {
            const constexpr bool sized_in { Utils::is_ancestor<Expression::Bits, In> };
            static_assert(Utils::TD::boolean<sized_in, In>,
                          "Create::Private::int_binary does not suppot sized output types without "
                          "sized input types");
        }

        // For brevity
        namespace Ex = Expression;
        using namespace Simplification;
        namespace Err = Error::Expression;

        // Type check
        static_assert(Utils::qualified_is_in<In, Allowed...>,
                      "Create::Private::int_binary requires In is in Allowed");
        Utils::affirm<Err::Type>(CUID::is_t<In>(expr),
                                 WHOAMI_WITH_SOURCE "Expression operand of incorrect type");

        // Construct expression (static casts are safe because of previous checks)
        if constexpr (Utils::is_ancestor<Ex::Bits, Out>) {
            static_assert(Utils::TD::boolean<Mode != SizeMode::NA, Out>,
                          "SizeMode::NA not allowed with sized output type");
            // Construct size
            Constants::UInt new_bit_length { integer };
            if constexpr (Mode == SizeMode::Add) {
                new_bit_length += bit_length(expr);
            }
            else if constexpr (Mode != SizeMode::Second) {
                static_assert(Utils::TD::false_<Out>,
                              "Create::Private::int_binary does not support the given SizeMode");
            }
            // Actually construct expression
            return simplify(Ex::factory<Out>(std::forward<EAnVec>(av), expr->symbolic,
                                             Op::factory<OpT>(expr, integer), new_bit_length));
        }
        else {
            static_assert(Mode == Utils::TD::id<SizeMode::NA>,
                          "SizeMode should be NA for non-sized type");
            return simplify(Ex::factory<Out>(std::forward<EAnVec>(av), expr->symbolic,
                                             Op::factory<OpT>(expr, integer)));
        }
    }

    /** Create a Expression with a int binary op
     *  A specialization where In = Out
     */
    template <typename IntT, typename InOut, typename OpT, SizeMode Mode, typename... Allowed>
    inline EBasePtr int_binary(EAnVec &&av, const EBasePtr &expr, const IntT integer) {
        return int_binary<IntT, InOut, InOut, OpT, Mode, Allowed...>(std::forward<EAnVec>(av),
                                                                     expr, integer);
    }

} // namespace Create::Private

#endif
