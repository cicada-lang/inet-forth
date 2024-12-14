#include "index.h"

// largest primes less than 2^n for n = 4...63

size_t hash_primes[] = {
    13, // 2^4
    31, // 2^5
    61, // 2^6
    127, // 2^7
    251, // 2^8
    509, // 2^9
    1021, // 2^10
    2039, // 2^11
    4093, // 2^12
    8191, // 2^13
    16381, // 2^14
    32749, // 2^15
    65521, // 2^16
    131071, // 2^17
    262139, // 2^18
    524287, // 2^19
    1048573, // 2^20
    2097143, // 2^21
    4194301, // 2^22
    8388593, // 2^23
    16777213, // 2^24
    33554393, // 2^25
    67108859, // 2^26
    134217689, // 2^27
    268435399, // 2^28
    536870909, // 2^29
    1073741789, // 2^30
    2147483647, // 2^31
    4294967295, // 2^32
    8589934591, // 2^33
    17179869183, // 2^34
    34359738367, // 2^35
    68719476735, // 2^36
    137438953471, // 2^37
    274877906943, // 2^38
    549755813887, // 2^39
    1099511627775, // 2^40
    2199023255551, // 2^41
    4398046511103, // 2^42
    8796093022207, // 2^43
    17592186044415, // 2^44
    35184372088831, // 2^45
    70368744177663, // 2^46
    140737488355327, // 2^47
    281474976710655, // 2^48
    562949953421311, // 2^49
    1125899906842623, // 2^50
    2251799813685247, // 2^51
    4503599627370495, // 2^52
    9007199254740991, // 2^53
    18014398509481983, // 2^54
    36028797018963967, // 2^55
    72057594037927935, // 2^56
    144115188075855871, // 2^57
    288230376151711743, // 2^58
    576460752303423487, // 2^59
    1152921504606846975, // 2^60
    2305843009213693949, // 2^61
    4611686018427387903, // 2^62
    9223372036854775807, // 2^63
};