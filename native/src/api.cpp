/** @file */
extern "C" {
#include "api.h"
}
#include "api_private.hpp"

// @todo: Handle exceptions


// Static checks
/** A local macro used for static tests */
#define SAME_U(A, B) (sizeof(A) == sizeof(B) && std::is_unsigned_v<A> && std::is_unsigned_v<B>)
static_assert(SAME_U(std::size_t, Constants::UInt), "Constants::UInt needs to be changed");
static_assert(SAME_U(SIZE_T, Constants::UInt), "Constants::UInt needs to be changed");
static_assert(SAME_U(VS_T, PyObj::Base::Ref), "VS_T needs to be changed");
static_assert(SAME_U(HASH_T, Hash::Hash), "HASH_T needs to be changed");
// Cleanup
#undef SAME_U

/********************************************************************/
/*                            Annotation                            */
/********************************************************************/

extern "C" {

ClaricppAnnotation *claricpp_annotation_new_base() {
    return API::to_c(Annotation::factory<Annotation::Base>());
}

ClaricppAnnotation *claricpp_annotation_new_simplification_avoicance() {
    return API::to_c(Annotation::factory<Annotation::SimplificationAvoidance>());
}

ClaricppSPAV *claricpp_annotation_create_spav(const ClaricppAnnotation *const *const list,
                                              const SIZE_T len) {
    Annotation::Vec::RawVec raw;
    raw.reserve(len);
    for (SIZE_T i = 0; i < len; ++i) {
        raw.emplace_back(list[i]->ptr); // NOLINT
    }
    using CV = Utils::InternalType<Annotation::SPAV>;
    return API::to_c(std::make_shared<CV>(std::move(raw)));
}
}

/********************************************************************/
/*                              Create                              */
/********************************************************************/

extern "C" {

// Symbol

ClaricppExpr *claricpp_create_symbol_bool(const char *const name) {
    return API::to_c(Create::symbol(std::string { name }));
}

/** A local macro used for consistency */
#define CREATE_SYM(TYPE, NAME)                                                                    \
    ClaricppExpr *claricpp_create_symbol_##NAME(const char *const name,                           \
                                                const SIZE_T bit_length) {                        \
        return API::to_c(Create::symbol<Expression::TYPE>(std::string { name }, bit_length));     \
    }

CREATE_SYM(String, string);
CREATE_SYM(VS, vs);
CREATE_SYM(FP, fp);
CREATE_SYM(BV, bv);

// Cleanup
#undef CREATE_SYM

// Literal

/** A local macro used for consistency */
#define CREATE_LIT(TYPE, NAME)                                                                    \
    ClaricppExpr *claricpp_create_literal_##NAME(const TYPE value) {                              \
        return API::to_c(Create::literal(value));                                                 \
    }

CREATE_LIT(bool, bool);
CREATE_LIT(float, fp_float);
CREATE_LIT(double, fp_double);
CREATE_LIT(uint8_t, bv_u8);
CREATE_LIT(uint16_t, bv_u16);
CREATE_LIT(uint32_t, bv_u32);
CREATE_LIT(uint64_t, bv_u64);

// Cleanup
#undef CREATE_LIT

ClaricppExpr *claricpp_create_literal_string(PyStr str) {
    return API::to_c(Create::literal(std::string { str }));
}

ClaricppExpr *claricpp_create_literal_vs(const HASH_T hash, const VS_T value,
                                         const SIZE_T bit_length) {
    return API::to_c(Create::literal(std::make_shared<PyObj::VS>(hash, value, bit_length)));
}

ClaricppExpr *claricpp_create_literal_bv_big_int_mode_str(PyStr value, const SIZE_T bit_length) {
    return API::to_c(Create::literal(BigInt { value, bit_length }));
}

ClaricppExpr *claricpp_create_literal_bv_big_int_mode_int(PyStr value, const SIZE_T bit_length) {
    return API::to_c(Create::literal(BigInt { BigInt::Int { value }, bit_length }));
}
}