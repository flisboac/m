#ifndef MTBASE_H_
#define MTBASE_H_

#define mt(S)              mt(S)
#define mt_t(S)            m_t(S)
#define mt_p(S)            m_p(S)
#define mt_at(S)           m_at(S)
#define mt_a(S)            m_a(S)
#define Mt(S)              m_a(S)
#define mt_f(S, n)         m_f(S)
#define mt_fp(S, n)        m_fp(S)

/**
 * A constant used on hash calculations.
 */
#define mt_HASH_C (0x45d9f3b)


/**
 * Initializes a scalar type to a zero value.
 */
#define mt_INITSCALAR(S, a, r) \
    a = ((mt(S))0)


/**
 * Initializes a non-scalar type to all-zero.
 */
#define mt_INITSTRUCT(S, a, r) \
    a = {0}


/**
 */
#define mt_QUIT(S, a, r)


/**
 */
#define mt_COPYVAL(S, a, b, r) \
    b = a


/**
 */
#define mt_COPYPTR(S, a, b, r)                                                 \
    do {                                                                       \
        size_t mt_COPYPTR_i;                                                   \
        for (mt_COPYPTR_i = 0; mt_COPYPTR_i < sizeof(mt_t(S)); mt_COPYPTR_i++) \
            b[mt_COPYPTR_i] = a[mt_COPYPTR_i];                                 \
    }


/**
 */
#define mt_VOPER(S, r, oper, nobjs, objs, to, init, quit, copy)                \
    do {                                                                       \
        mt(S) *mt_VOPERX_o = (objs), *mt_VOPERX_t = (to);                      \
        size_t mt_VOPERX_i, mt_VOPERX_n = (nobjs);                             \
        int mt_VOPERX_op = (oper);                                             \
        mt_VOPERX_r = m_OK;                                                    \
        if (!mt_VOPERX_o) mt_VOPERX_r = m_ERRMISS;                             \
        else switch(mt_VOPERX_op) {                                            \
            case m_VAL_INIT:                                                   \
                for (mt_VOPERX_i = 0; mt_VOPERX_i < mt_VOPERX_n; mt_VOPERX_i++)\
                {                                                              \
                    init(S, mt_VOPERX_o[mt_VOPERX_i], mt_VOPERX_r);            \
                    if (mt_VOPERX_r > 0) break;                                \
                };                                                             \
                break;                                                         \
            case m_VAL_QUIT:                                                   \
                for (mt_VOPERX_i = 0; mt_VOPERX_i < mt_VOPERX_n; mt_VOPERX_i++)\
                {                                                              \
                    quit(S, mt_VOPERX_o[mt_VOPERX_i], mt_VOPERX_r);            \
                    if (mt_VOPERX_r > 0) break;                                \
                };                                                             \
                break;                                                         \
            case m_VAL_COPY:                                                   \
                if (!mt_VOPERX_t) mt_VOPERX_r = m_ERRMISS;                     \
                else for (mt_VOPERX_i = 0; mt_VOPERX_i < n; mt_VOPERX_i++) {   \
                        copy(S                                                 \
                            , mt_VOPERX_o[mt_VOPERX_i]                         \
                            , mt_VOPERX_t[mt_VOPERX_i]                         \
                            , mt_VOPERX_r);                                    \
                        if (mt_VOPERX_r > 0) break;                            \
                    };                                                         \
                break;                                                         \
            default: mt_VOPERX_r = m_ERRSUPP; break;                           \
        }                                                                      \
    }


/**
 * Does a pretty simple comparison between two scalar types.
 * This macro can be applied to integers, pointers and (to some extent)
 * floats.
 * The comparison is independent of type size.
 */
#define mt_CMPSCALAR(S, r, a, b)                                               \
    do {                                                                       \
        mt(S) mt_CMPSCALAR_a = (a);                                            \
        mt(S) mt_CMPSCALAR_b = (b);                                            \
        r = (mt_CMPSCALAR_a > mt_CMPSCALAR_b) - (mt_CMPSCALAR_a < mt_CMPSCALAR_b);\
    }


/**
 * Does a pretty rudimentar and naive comparison between two non-scalar types.
 * Caution, this comparison is value-based! For a pointer-based comparison, use
 * #mt_CMPPSTRUCT
 */
#define mt_CMPSTRUCT(S, r, a, b)                                               \
    do {                                                                       \
        mt(S) mt_CMPSTRUCT_a = (a);                                            \
        mt(S) mt_CMPSTRUCT_b = (b);                                            \
        char* mt_CMPSTRUCT_pa = (char*)&mt_CMPSTRUCT_a;                        \
        char* mt_CMPSTRUCT_pb = (char*)&mt_CMPSTRUCT_b;                        \
        size_t mt_CMPSTRUCT_i;                                                 \
        for (mt_CMPSTRUCT_i = 0; mt_CMPSTRUCT_i < sizeof(mt(S); mt_CMPSTRUCT_i++)\
        {                                                                      \
            mt_CMPSTRUCT_r = (                                                 \
                    mt_CMPSTRUCT_pa[mt_CMPSTRUCT_i]                            \
                    > mt_CMPSTRUCT_pb[mt_CMPSTRUCT_i])                         \
                - ( mt_CMPSTRUCT_pa[mt_CMPSTRUCT_i]                            \
                    < mt_CMPSTRUCT_pb[mt_CMPSTRUCT_i]);                        \
            if (mt_CMPSTRUCT_r) break;                                         \
        }                                                                      \
    }


/**
 * Does a pretty rudimentar and naive comparison between two pointers to
 * non-scalar types.
 * This is a poor-man's comparison algorithm. PLEASE DO your own comparer!
 */
#define mt_CMPPSTRUCT(S, r, a, b)                                              \
    do {                                                                       \
        char* mt_CMPPSTRUCT_pa = (char*)a;                                     \
        char* mt_CMPPSTRUCT_pb = (char*)b;                                     \
        size_t mt_CMPPSTRUCT_i;                                                \
        for (mt_CMPPSTRUCT_i = 0; mt_CMPPSTRUCT_i < sizeof(mt(S); mt_CMPPSTRUCT_i++)\
        {                                                                      \
            mt_CMPPSTRUCT_r = (                                                \
                    mt_CMPPSTRUCT_pa[mt_CMPPSTRUCT_i]                          \
                    > mt_CMPPSTRUCT_pb[mt_CMPPSTRUCT_i])                       \
                - ( mt_CMPPSTRUCT_pa[mt_CMPPSTRUCT_i]                          \
                    < mt_CMPPSTRUCT_pb[mt_CMPPSTRUCT_i]);                      \
            if (mt_CMPPSTRUCT_r) break;                                        \
        }                                                                      \
    }


/**
 */
#define mt_CMPWSTR(S, r, a, b) \
    r = wcscmp(a, b);         \


/**
 */
#define mt_CMPWCOLL(S, r, a, b) \
    r = wcscoll(a, b);          \


/**
 */
#define mt_CMPSTR(S, r, a, b) \
    r = strcmp(a, b);         \


/**
 */
#define mt_CMPCOLL(S, r, a, b) \
    r = strcoll(a, b);          \


/**
 */
#define mt_HASHVAL(S, r, a, C, L)    \
    do {                             \
        r = ((size_t)(a));           \
        r = ((r >> 16) ^ r) * C;     \
        r = ((r >> 16) ^ r) * C;     \
        r = ((r >> 16) ^ r);         \
        r = r % L;                   \
    }


/**
 */
#define mt_HASHSTR(S, r, a, C, L)                  \
    do {                                           \
        mt(S) mt_HASHSTR_a = a;                    \
        while (*mt_HASHSTR_a) {                    \
            mt_HASHVAL(S, r, *mt_HASHSTR_a, C, L); \
        }                                          \
    }


/**
 */
#define mt_HASHWSTR mt_HASHSTR


/**
 */
#define mt_HASHSTRUCT(S, r, a, C, L)               \
    do {                                           \
        mt(S) mt_HASHSTRUCT_a = a;
        char* mt_HASHSTRUCT_pa = (char*)&a;
        size_t mt_HASHSTRUCT_i;
        for (mt_HASHSTRUCT_i = 0; mt_HASHSTRUCT_i < sizeof(mt(S)); mt_HASHSTRUCT_i++) {\
            mt_HASHVAL(S, r, mt_HASHSTRUCT_pa[mt_HASHSTRUCT_i], C, L); \
        }
    }


/**
 */
#define mt_HASH(S, r, a, F) \
    F(S, r, a, mt_HASH_C, m_MAXSZ)


#endif /* MTBASE_H_ */
