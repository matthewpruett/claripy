/**
 * @file
 * @brief This file defines a function to link Python and C++ exceptions
 */
#ifndef R_API_EXCEPTIONS_HPP_
#define R_API_EXCEPTIONS_HPP_

#include <pybind11/pybind11.h>

namespace API {
    /** Register exceptions with pybind11 */
    void bind_exceptions(pybind11::module_ &);
} // namespace API

#endif
