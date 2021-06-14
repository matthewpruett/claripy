/**
 * @file
 * \ingroup utils
 * @brief This file defines the function norm_path_hash
 */
#ifndef R_UTILS_NORMPATHHASH_HPP_
#define R_UTILS_NORMPATHHASH_HPP_

#include "affirm.hpp"
#include "error.hpp"
#include "fnv1a.hpp"
#include "str_prefix.hpp"

#include "../constants.hpp"

#include <array>


namespace Utils {

    /** Return the FNV1a of the normal path of s
     *  Len must be the length of s
     *  Will throw in noexcept context if s goes outside of '/' or './' (depending on the prefix)
     *  For example /../foo is not ok; likewise ./../foo is not ok. But /bar/../foo is fine
     */
    template <Constants::UInt Len> constexpr uint64_t norm_path_hash(const char *s) noexcept {

        // Trivial case
        auto len { Len };
        if (len == 0) {
            return 0;
        }

/** A local macro used to advance s */
#define ADVANCE(X)                                                                                \
    {                                                                                             \
        s += (X);                                                                                 \
        len -= (X);                                                                               \
    }

        // Determine if absolute or relative path
        const bool absolute { s[0] == '/' };
        if (absolute) {
            while (len && s[0] == '/') {
                ADVANCE(1);
            };
        }

        // Store path segments
        std::array<const char *, Len> segments {};
        std::array<Constants::UInt, Len> segment_lengths {};
        Constants::UInt n_seg { 0 };

        // Current segment info
        Constants::UInt offset { 0 };
        Constants::UInt current_seg_length { 0 };

        // Repeat for all of s
        while (len) {
            // Handle './' and '//'
            if (str_prefix(s, "./") || str_prefix(s, "//")) {
                ADVANCE(1);
                ++offset;
            }
            // Segment update
            if (s[0] == '/') {
                // Skip empty segments
                if (current_seg_length) {
                    segments[n_seg] = s - offset - current_seg_length;
                    segment_lengths[n_seg] = current_seg_length;
                    ++n_seg;
                }
                // Reset current segment data
                current_seg_length = 0;
                offset = 0;
                ADVANCE(1);
                continue;
            }
            // Handle '../'
            if (str_prefix(s, "../")) {
                ADVANCE(3)
                // Rewinding segments
                affirm<Error::Unexpected::BadPath>(n_seg > 0, WHOAMI_WITH_SOURCE,
                                                   "given path that goes outside of / or ./");
                n_seg -= 1;
                continue;
            }
            // Normal character
            ADVANCE(1)
            ++current_seg_length;
        }

// Cleanup
#undef ADVANCE

        // Record last segment
        segments[n_seg] = s - current_seg_length;
        segment_lengths[n_seg] = current_seg_length;
        ++n_seg;

        // Construct norm path
        std::array<char, Len + 3> norm {};
        Constants::UInt n_len { 0 };
        if (!absolute) {
            norm[n_len++] = '.';
        }
        norm[n_len++] = '/';
        for (Constants::UInt i { 0 }; i < n_seg; ++i) {
            for (Constants::UInt k { 0 }; k < segment_lengths[i]; ++k) {
                norm[n_len++] = segments[i][k];
            }
            norm[n_len++] = '/';
        }
        norm[--n_len] = 0;

        // Hash
        return FNV1a<char>::u64(norm.data(), n_len);
    }

} // namespace Utils

#endif