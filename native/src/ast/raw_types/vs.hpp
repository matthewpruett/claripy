/**
 * @file
 * @brief This file defines the AST::RawTypes::VS class and defines AST::VS
 */
#ifndef __AST_RAWTYPES_VS_HPP__
#define __AST_RAWTYPES_VS_HPP__

#include "bits.hpp"


/** A namespace used for the ast directory */
namespace AST {

    /** A namespace which contains the raw AST types that are constructed via AST::factory
     *  These classes are unlikely to be accessed directly, but rather should be via a shared_ptr
     */
    namespace RawTypes {

        /** An AST representing a value set */
        class VS : public Bits {

            /** Return the name of the type this class represents irrespective of length */
            std::string fundamental_type_name() const;

            /** A private constructor to disallow public creation
             *  This must have take in the same arguments as the hash function, minus the hash
             *  which must be the first argument passed
             */
            VS(const Hash h, const Ops::Operation o);

            /** Delete all default constructors */
            DELETE_DEFAULTS(VS)

            /** The hash function of this AST
             *  This must have take in the same arguments as the constructor, minus the hash
             * @todo not exactly, args in the constructor can consume inputs
             */
            static Hash hash(const Ops::Operation o);

            /** Allow factories friend access */
            template <typename T, typename... Args>
            friend T factory(std::set<BackendID> &&eager_backends, Args &&...args);

            /** Allow cache friend access
             *  We expose the constructor so that the cache may emplace new objects, which is
             *  faster than copying them in
             */
            friend class ::AST::Private::Cache<Hash, Base>;
        };

    } // namespace RawTypes

} // namespace AST

#endif
