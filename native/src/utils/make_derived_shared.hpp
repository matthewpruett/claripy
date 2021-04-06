/**
 * @file
 * \ingroup utils
 * @brief This file defines a function to make a shared_ptr<Base> of of a Derived
 * These casts preserve the constness of the internal type
 */
#ifndef __UTILS_MAKEDERIVEDSHARED_HPP__
#define __UTILS_MAKEDERIVEDSHARED_HPP__

#include "pointer_cast.hpp"
#include "transfer_const.hpp"

#include <memory>
#include <type_traits>


namespace Utils {

    /** Make an std::shared_ptr<Base> from a Derived with args Args
     *  Note: If Base is const, a const Derived is made
     */
    template <typename Base, typename Derived, typename... Args>
    inline std::shared_ptr<Base> make_derived_shared(Args &&...args) {
        // Static verification
        static_assert(is_ancestor<Base, Derived>, "Derived must derive from Base");
        if constexpr (std::is_const_v<Derived>) {
            static_assert(std::is_const_v<Base>, "Derived is const, so Base must also be const");
        }
        // Transfer constness
        using TrueDerived = TransferConst<Derived, Base>;
        if constexpr (is_same_ignore_const<Base, Derived>) {
            return std::make_shared<TrueDerived>(std::forward<Args>(args)...);
        }
        else {
            // Return initialize a static up cast from a new Derived constructed via fowarded args
            return up_cast<Base>(std::make_shared<TrueDerived>(std::forward<Args>(args)...));
        }
    }

} // namespace Utils

#endif