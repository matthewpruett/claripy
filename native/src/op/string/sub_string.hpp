/**
 * @file
 * @brief This file defines the String::SubString class
 */
#ifndef R_OP_STRING_SUBSTRING_HPP_
#define R_OP_STRING_SUBSTRING_HPP_

#include "../base.hpp"


namespace Op::String {

    /** The op class: String::SubString */
    class SubString final : public Base {
        OP_FINAL_INIT(SubString, 0, "String::");

      public:
        /** The start index of the substring stored as a BV
         *  Note: We leave it as a base for optimizations purposes
         */
        const Expression::BasePtr start_index;
        /** The count of the substring stored as a BV
         *  Note: We leave it as a base for optimizations purposes
         */
        const Expression::BasePtr count;
        /** The count of the substring stored as a String
         *  Note: We leave it as a base for optimizations purposes
         */
        const Expression::BasePtr full_string;

        /** Python's repr function (outputs json) */
        inline void repr(std::ostringstream &out,
                         const bool verbose = false) const override final {
            out << R"|({ "name":")|" << op_name() << R"|(", "start_index":)|";
            Expression::repr(start_index, out, verbose);
            out << R"|(, "count":)|";
            Expression::repr(count, out, verbose);
            out << R"|(, "full_string":)|";
            Expression::repr(full_string, out, verbose);
            out << " }";
        }

        /** Add's the raw expression children of the expression to the given stack in reverse
         *  Warning: This does *not* give ownership, it transfers raw pointers
         */
        inline void add_reversed_children(Stack &s) const override final {
            s.emplace(full_string.get());
            s.emplace(count.get());
            s.emplace(start_index.get());
        }

      private:
        /** Protected constructor
         *  Ensure that each argument is of the proper type
         */
        explicit inline SubString(const Hash::Hash &h, const Expression::BasePtr &si,
                                  const Expression::BasePtr &c, const Expression::BasePtr &s)
            : Base { h, static_cuid }, start_index { si }, count { c }, full_string { s } {
            using Err = Error::Expression::Type;
            Utils::affirm<Err>(CUID::is_t<Expression::BV>(start_index),
                               WHOAMI_WITH_SOURCE "start_index expression must be a BV");
            Utils::affirm<Err>(CUID::is_t<Expression::BV>(count),
                               WHOAMI_WITH_SOURCE "count expression must be a BV");
            Utils::affirm<Err>(CUID::is_t<Expression::String>(full_string),
                               WHOAMI_WITH_SOURCE "full_string expression must be a String");
        }
    };

} // namespace Op::String

#endif