/**
 * @file
 * \ingroup utils
 * @brief This file determines a function which checks if T has a << stream op
 */
#ifndef R_UTILS_PRIVATE_HASOSTREAMOP_HPP_
#define R_UTILS_PRIVATE_HASOSTREAMOP_HPP_

#include "../sfinae_test.hpp"

#include <ostream>


namespace Utils::Private {

    /** A struct which determines if T has a << stream op defined */
    UTILS_SFINAETEST(has_ostream_op,                       // Invoke this
                     HasOStreamOp,                         // Internal class name
                     *static_cast<std::ostream *>(nullptr) // declval is buggy so we cast
                         << std::declval<U>(),             // Condition we are checking
                     typename T                            // Template arguments
    )

} // namespace Utils::Private

#endif
