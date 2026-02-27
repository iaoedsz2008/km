
#ifndef UNTITLED_STRINGHASHV2_H
#define UNTITLED_STRINGHASHV2_H

#include "SecureSeed.h"

#define XXH_PRIME32_1 0x9E3779B1U /*!< 0b10011110001101110111100110110001 */
#define XXH_PRIME32_2 0x85EBCA77U /*!< 0b10000101111010111100101001110111 */
#define XXH_PRIME32_3 0xC2B2AE3DU /*!< 0b11000010101100101010111000111101 */
#define XXH_PRIME32_4 0x27D4EB2FU /*!< 0b00100111110101001110101100101111 */
#define XXH_PRIME32_5 0x165667B1U /*!< 0b00010110010101100110011110110001 */

#define XXH_PRIME64_1 0x9E3779B185EBCA87ULL /*!< 0b1001111000110111011110011011000110000101111010111100101010000111 */
#define XXH_PRIME64_2 0xC2B2AE3D27D4EB4FULL /*!< 0b1100001010110010101011100011110100100111110101001110101101001111 */
#define XXH_PRIME64_3 0x165667B19E3779F9ULL /*!< 0b0001011001010110011001111011000110011110001101110111100111111001 */
#define XXH_PRIME64_4 0x85EBCA77C2B2AE63ULL /*!< 0b1000010111101011110010100111011111000010101100101010111001100011 */
#define XXH_PRIME64_5 0x27D4EB2F165667C5ULL /*!< 0b0010011111010100111010110010111100010110010101100110011111000101 */

// https://github.com/ekpyron/xxhashct
namespace StringHash {

static constexpr uint32_t
XXH_rotl32_(uint32_t x, int r)
{
    return (((x) << (r)) | ((x) >> (32 - (r))));
}

static constexpr uint64_t
XXH_rotl64_(uint64_t x, int r)
{
    return (((x) << (r)) | ((x) >> (64 - (r))));
}

static constexpr uint32_t
XXH_get32bits_(const char* p)
{
    return ((uint32_t)(uint8_t)p[0] << 0x00) | ((uint32_t)(uint8_t)p[1] << 0x08) | ((uint32_t)(uint8_t)p[2] << 0x10) | ((uint32_t)(uint8_t)p[3] << 0x18);
}

static constexpr uint64_t
XXH_get64bits_(const char* p)
{
    return ((uint64_t)(uint8_t)p[0] << 0x00) | ((uint64_t)(uint8_t)p[1] << 0x08) | ((uint64_t)(uint8_t)p[2] << 0x10) | ((uint64_t)(uint8_t)p[3] << 0x18) | ((uint64_t)(uint8_t)p[4] << 0x20) | ((uint64_t)(uint8_t)p[5] << 0x28) | ((uint64_t)(uint8_t)p[6] << 0x30) | ((uint64_t)(uint8_t)p[7] << 0x38);
}

#if 1 // XXH32

static constexpr uint32_t
XXH32_round(uint32_t acc, uint32_t input)
{
    return XXH_rotl32_(acc + (input * XXH_PRIME32_2), 13) * XXH_PRIME32_1;
}

static constexpr uint32_t
XXH32_avalanche0(uint32_t hash)
{
    return (hash ^ (hash >> 15)) * XXH_PRIME32_2;
}

static constexpr uint32_t
XXH32_avalanche1(uint32_t hash)
{
    return (hash ^ (hash >> 13)) * XXH_PRIME32_3;
}

static constexpr uint32_t
XXH32_avalanche2(uint32_t hash)
{
    return hash ^ (hash >> 16);
}

static constexpr uint32_t
XXH32_avalanche(uint32_t hash)
{
    return XXH32_avalanche2(XXH32_avalanche1(XXH32_avalanche0(hash)));
}

static constexpr uint32_t
XXH32_finalize(uint32_t hash, const char* p, int len)
{
    return (len >= 4) ? (XXH32_finalize(XXH_rotl32_(hash + (XXH_get32bits_(p) * XXH_PRIME32_3), 17) * XXH_PRIME32_4, p + 4, len - 4)) : ((len > 0) ? (XXH32_finalize(XXH_rotl32_(hash + ((uint32_t)(uint8_t)p[0] * XXH_PRIME32_5), 11) * XXH_PRIME32_1, p + 1, len - 1)) : XXH32_avalanche(hash));
}

static constexpr uint32_t
XXH32_endian_align(const char* p, uint32_t len, const uint32_t v1, const uint32_t v2, const uint32_t v3, const uint32_t v4)
{
    return (len >= 16) ? XXH32_endian_align(p + 16, len - 16, XXH32_round(v1, XXH_get32bits_(p)), XXH32_round(v2, XXH_get32bits_(p + 4)), XXH32_round(v3, XXH_get32bits_(p + 8)), XXH32_round(v4, XXH_get32bits_(p + 12))) : XXH_rotl32_(v1, 1) + XXH_rotl32_(v2, 7) + XXH_rotl32_(v3, 12) + XXH_rotl32_(v4, 18);
}

static constexpr uint32_t
XXH32_endian_align(const char* p, uint32_t len, const uint32_t seed)
{
    return XXH32_endian_align(p, len, seed + XXH_PRIME32_1 + XXH_PRIME32_2, seed + XXH_PRIME32_2, seed, seed - XXH_PRIME32_1);
}

static constexpr uint32_t
MYXXH32(const char* p, int len, uint32_t seed)
{
    return XXH32_finalize((len >= 16 ? XXH32_endian_align(p, len, seed) : seed + XXH_PRIME32_5) + len, p + (len & ~0xF), len & 0xF);
}

template <size_t N>
static constexpr uint32_t
MYXXH32(const char (&s)[N], uint32_t seed)
{
    return MYXXH32(s, N - 1, seed);
}

#endif

#if 1 // XXH64

static constexpr uint64_t
XXH64_round(uint64_t acc, uint64_t input)
{
    return XXH_rotl64_(acc + input * XXH_PRIME64_2, 31) * XXH_PRIME64_1;
}

static constexpr uint64_t
XXH64_mergeRound(uint64_t acc, uint64_t val)
{
    return (acc ^ XXH64_round(0, val)) * XXH_PRIME64_1 + XXH_PRIME64_4;
}

static constexpr uint64_t
XXH64_avalanche0(uint64_t hash)
{
    return (hash ^ (hash >> 33)) * XXH_PRIME64_2;
}

static constexpr uint64_t
XXH64_avalanche1(uint64_t hash)
{
    return (hash ^ (hash >> 29)) * XXH_PRIME64_3;
}

static constexpr uint64_t
XXH64_avalanche2(uint64_t hash)
{
    return hash ^ (hash >> 32);
}

static constexpr uint64_t
XXH64_avalanche(uint64_t hash)
{
    return XXH64_avalanche2(XXH64_avalanche1(XXH64_avalanche0(hash)));
}

static constexpr uint64_t
XXH64_finalize(uint64_t hash, const char* p, int len)
{
    return (len >= 8) ? (XXH64_finalize(XXH_rotl64_(hash ^ XXH64_round(0, XXH_get64bits_(p)), 27) * XXH_PRIME64_1 + XXH_PRIME64_4, p + 8, len - 8)) : ((len >= 4) ? (XXH64_finalize(XXH_rotl64_(hash ^ ((uint64_t)XXH_get32bits_(p) * XXH_PRIME64_1), 23) * XXH_PRIME64_2 + XXH_PRIME64_3, p + 4, len - 4)) : ((len > 0) ? (XXH64_finalize(XXH_rotl64_(hash ^ ((uint64_t)(uint8_t)p[0] * XXH_PRIME64_5), 11) * XXH_PRIME64_1, p + 1, len - 1)) : XXH64_avalanche(hash)));
}

static constexpr uint64_t
XXH64_endian_align(const char* p, uint64_t len, const uint64_t v1, const uint64_t v2, const uint64_t v3, const uint64_t v4)
{
    return (len >= 32) ? XXH64_endian_align(p + 32, len - 32, XXH64_round(v1, XXH_get64bits_(p)), XXH64_round(v2, XXH_get64bits_(p + 8)), XXH64_round(v3, XXH_get64bits_(p + 16)), XXH64_round(v4, XXH_get64bits_(p + 24))) : XXH64_mergeRound(XXH64_mergeRound(XXH64_mergeRound(XXH64_mergeRound(XXH_rotl64_(v1, 1) + XXH_rotl64_(v2, 7) + XXH_rotl64_(v3, 12) + XXH_rotl64_(v4, 18), v1), v2), v3), v4);
}

static constexpr uint64_t
XXH64_endian_align(const char* p, uint64_t len, const uint64_t seed)
{
    return XXH64_endian_align(p, len, seed + XXH_PRIME64_1 + XXH_PRIME64_2, seed + XXH_PRIME64_2, seed, seed - XXH_PRIME64_1);
}

static constexpr uint64_t
MYXXH64(const char* p, int len, uint64_t seed)
{
    return XXH64_finalize((len >= 32 ? XXH64_endian_align(p, len, seed) : seed + XXH_PRIME64_5) + len, p + (len & ~0x1F), len & 0x1F);
}

template <size_t N>
static constexpr uint64_t
MYXXH64(const char (&s)[N], uint64_t seed)
{
    return MYXXH64(s, N - 1, seed);
}

#endif

template <uint32_t K>
struct __Hash32__ {
    static constexpr uint32_t value = K;
};

template <uint64_t K>
struct __Hash64__ {
    static constexpr uint64_t value = K;
};

template <uint64_t K>
struct __Constants__ {};

template <uint64_t K>
struct __Constants16__ {};

template <uint64_t K>
struct __Constants32__ {};

template <uint64_t K>
struct __Constants64__ {};

template <uint64_t _Type, uint64_t _Field>
struct __Field__ {};

}; // namespace StringHash

#define Hash32(__name__) StringHash::__Hash32__<StringHash::MYXXH32(__name__, SecureSeed32)>::value
#define Hash64(__name__) StringHash::__Hash64__<StringHash::MYXXH64(__name__, SecureSeed64)>::value

#define DefineConst(__name__, __value__)                 \
    template <>                                          \
    struct StringHash::__Constants__<Hash64(__name__)> { \
        static constexpr auto value = __value__;         \
        using type = decltype(value);                    \
    }

#define DefineConst16(__name__, __value__)                 \
    template <>                                            \
    struct StringHash::__Constants16__<Hash64(__name__)> { \
        static constexpr uint16_t value = __value__;       \
    }

#define DefineConst32(__name__, __value__)                 \
    template <>                                            \
    struct StringHash::__Constants32__<Hash64(__name__)> { \
        static constexpr uint32_t value = __value__;       \
    }

#define DefineConst64(__name__, __value__)                 \
    template <>                                            \
    struct StringHash::__Constants64__<Hash64(__name__)> { \
        static constexpr uint64_t value = __value__;       \
    }

#define DefineField(__struct__, __field__, __type__, __offset__)          \
    template <>                                                           \
    struct StringHash::__Field__<Hash64(__struct__), Hash64(__field__)> { \
        using type = __type__;                                            \
        static constexpr size_t offset = __offset__;                      \
    }

#define Field(__struct__, __field__) StringHash::__Field__<Hash64(__struct__), Hash64(__field__)>
#define Const(__name__)              StringHash::__Constants__<Hash64(__name__)>::value
#define Const16(__name__)            StringHash::__Constants16__<Hash64(__name__)>::value
#define Const32(__name__)            StringHash::__Constants32__<Hash64(__name__)>::value
#define Const64(__name__)            StringHash::__Constants64__<Hash64(__name__)>::value

#if INTPTR_MAX == INT64_MAX
#define Hash Hash64
#else
#define Hash Hash32
#endif

#endif
