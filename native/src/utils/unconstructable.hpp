/**
 * @file
 * @brief This file defines an unconstructable class
 */
#ifndef __UTILS_UNCONSTRUCTABLE_HPP__
#define __UTILS_UNCONSTRUCTABLE_HPP__

#include "../macros.hpp"


/** A namespace used for the utils directory */
namespace Utils {

    /** An unconstructable class */
    class Unconstructable {
        DELETE_DEFAULTS(Unconstructable);
        /** Disable Destruction */
        ~Unconstructable() = delete;
    };

} // namespace Utils

#endif