/**
 * @file
 * @brief This file define helpers to Utils::to_str
 */
#ifndef __UTILS_PRIVATE_TOSTR_HPP__
#define __UTILS_PRIVATE_TOSTR_HPP__

#include <sstream>


/** A namespace used for the utils directory */
namespace Utils {

    /** A namespace used to designate certain items in utils as private
     *  These functions should not be called outside of the utils directory
     *  This is useful for helper functions templated functions call
     */
    namespace Private {

        /** This function takes in a set of arguments, and returns a string that comprises them
         *  Each argument must have the << stream operator defined
         *  This specialization takes has only one thing to add to the string
         */
        template <typename T> void to_str(std::stringstream &s, const T &next) { s << next; }

        /** This function takes in a set of arguments, and returns a string that comprises them
         *  Each argument must have the << stream operator defined
         */
        template <typename T, typename... Args>
        void to_str(std::stringstream &s, const T &next, const Args &...args) {
            s << next;
            to_str(s, args...);
        }

    } // namespace Private

} // namespace Utils

#endif