/**
 * @file
 * \ingroup utils
 * @brief This file defines a few terminal colors for pretty printing
 */
#ifndef R_UTILS_ANSICOLORCODES_HPP_
#define R_UTILS_ANSICOLORCODES_HPP_

#include "../constants.hpp"


#ifdef ENABLE_ANSI_COLOR_CODES
    /** Local: return X if ansi color codes are enabled, else "" */
    #define IF_ENABLED(X) (X)
#else
    /** Local: return X if ansi color codes are enabled, else "" */
    #define IF_ENABLED(X) ("")
#endif


namespace Utils::ANSIColorCodes {

    // Clear color codes
    constexpr CCSC reset { IF_ENABLED("\e[0m") };

    // Regular
    constexpr CCSC blk { IF_ENABLED("\e[0;30m") };
    constexpr CCSC red { IF_ENABLED("\e[0;31m") };
    constexpr CCSC grn { IF_ENABLED("\e[0;32m") };
    constexpr CCSC yel { IF_ENABLED("\e[0;33m") };
    constexpr CCSC blu { IF_ENABLED("\e[0;34m") };
    constexpr CCSC mag { IF_ENABLED("\e[0;35m") };
    constexpr CCSC cyn { IF_ENABLED("\e[0;36m") };
    constexpr CCSC wht { IF_ENABLED("\e[0;37m") };

    namespace Bold {
        constexpr CCSC blk { IF_ENABLED("\e[1;30m") };
        constexpr CCSC red { IF_ENABLED("\e[1;31m") };
        constexpr CCSC grn { IF_ENABLED("\e[1;32m") };
        constexpr CCSC yel { IF_ENABLED("\e[1;33m") };
        constexpr CCSC blu { IF_ENABLED("\e[1;34m") };
        constexpr CCSC mag { IF_ENABLED("\e[1;35m") };
        constexpr CCSC cyn { IF_ENABLED("\e[1;36m") };
        constexpr CCSC wht { IF_ENABLED("\e[1;37m") };
    } // namespace Bold

    namespace Underline {
        constexpr CCSC blk { IF_ENABLED("\e[4;30m") };
        constexpr CCSC red { IF_ENABLED("\e[4;31m") };
        constexpr CCSC grn { IF_ENABLED("\e[4;32m") };
        constexpr CCSC yel { IF_ENABLED("\e[4;33m") };
        constexpr CCSC blu { IF_ENABLED("\e[4;34m") };
        constexpr CCSC mag { IF_ENABLED("\e[4;35m") };
        constexpr CCSC cyn { IF_ENABLED("\e[4;36m") };
        constexpr CCSC wht { IF_ENABLED("\e[4;37m") };
    } // namespace Underline

    namespace HighIntensity {

        // Regular
        constexpr CCSC blk { IF_ENABLED("\e[0;90m") };
        constexpr CCSC red { IF_ENABLED("\e[0;91m") };
        constexpr CCSC grn { IF_ENABLED("\e[0;92m") };
        constexpr CCSC yel { IF_ENABLED("\e[0;93m") };
        constexpr CCSC blu { IF_ENABLED("\e[0;94m") };
        constexpr CCSC mag { IF_ENABLED("\e[0;95m") };
        constexpr CCSC cyn { IF_ENABLED("\e[0;96m") };
        constexpr CCSC wht { IF_ENABLED("\e[0;97m") };

        namespace Bold {
            constexpr CCSC blk { IF_ENABLED("\e[1;90m") };
            constexpr CCSC red { IF_ENABLED("\e[1;91m") };
            constexpr CCSC grn { IF_ENABLED("\e[1;92m") };
            constexpr CCSC yel { IF_ENABLED("\e[1;93m") };
            constexpr CCSC blu { IF_ENABLED("\e[1;94m") };
            constexpr CCSC mag { IF_ENABLED("\e[1;95m") };
            constexpr CCSC cyn { IF_ENABLED("\e[1;96m") };
            constexpr CCSC wht { IF_ENABLED("\e[1;97m") };
        } // namespace Bold

    } // namespace HighIntensity

    namespace Background {

        // Regular
        constexpr CCSC blk { IF_ENABLED("\e[40m") };
        constexpr CCSC red { IF_ENABLED("\e[41m") };
        constexpr CCSC grn { IF_ENABLED("\e[42m") };
        constexpr CCSC yel { IF_ENABLED("\e[43m") };
        constexpr CCSC blu { IF_ENABLED("\e[44m") };
        constexpr CCSC mag { IF_ENABLED("\e[45m") };
        constexpr CCSC cyn { IF_ENABLED("\e[46m") };
        constexpr CCSC wht { IF_ENABLED("\e[47m") };

        namespace HighIntensity {
            constexpr CCSC blk { IF_ENABLED("\e[0;100m") };
            constexpr CCSC red { IF_ENABLED("\e[0;101m") };
            constexpr CCSC grn { IF_ENABLED("\e[0;102m") };
            constexpr CCSC yel { IF_ENABLED("\e[0;103m") };
            constexpr CCSC blu { IF_ENABLED("\e[0;104m") };
            constexpr CCSC mag { IF_ENABLED("\e[0;105m") };
            constexpr CCSC cyn { IF_ENABLED("\e[0;106m") };
            constexpr CCSC wht { IF_ENABLED("\e[0;107m") };
        } // namespace HighIntensity

    } // namespace Background

} // namespace Utils::ANSIColorCodes

// Cleanup
#undef IF_ENABLED

#endif
