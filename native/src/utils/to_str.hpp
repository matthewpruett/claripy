/**
 * @file
 * @brief This file defines Utils::to_str
 */
#ifndef __UTILS_TOSTR_HPP__
#define __UTILS_TOSTR_HPP__

#include "apply.hpp"
#include "private/ostream.hpp"

#include <sstream>


/** A namespace used for the utils directory */
namespace Utils {

    /** This function takes in a set of arguments, and returns a string that comprises them
     *  Arguments are taken in by constant reference
     *  Each argument must have the << stream operator defined
     */
    template <typename... Args> std::string to_str(const Args &...args) {
        std::ostringstream s;
        apply<Private::OStreamConst>(s, args...);
        return s.str();
    }

} // namespace Utils

#endif
