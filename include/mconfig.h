#ifndef MCONFIG_H_
#define MCONFIG_H_


/*==============================================================================
 * [[[   C O N F I G U R A T I O N   ]]]
 * m_RELEASENAME 'define' and m_USER* markers can also be defined here,
 * if needed (in fact, that's the preferred way).
 */

#define m_NAME "macro"
#define m_MAJORVERSION 0
#define m_MINORVERSION 1
#define m_PATCHVERSION 0
#define m_RELEASETYPE  "beta"


/*==============================================================================
 * [[[   D E F I N I T I O N S   ]]]
 * Do not change what is below this line, unless you know what you're doing.
 */

#define m_STRQT(s) #s
#define m_STRFY(s) um_STRQT(s)


#ifndef m_BUILDINGDOCS

/** The release name. Do not change! */
#ifndef m_RELEASENAME
#   define m_RELEASENAME m_NAME \
    " " m_STRFY(m_MAJORVERSION) \
    "." m_STRFY(m_MINORVERSION) \
    "." m_STRFY(m_PATCHVERSION) \
    "-" m_RELEASETYPE
#endif

#if __STDC_VERSION__ = 199901L
#   define m_RESTRICT restrict
#elif defined(_WIN32)
#   define m_RESTRICT __declspec(restrict)
#elif defined(__GNUC__)
#   define m_RESTRICT __restrict__
#else
#   define m_RESTRICT
#endif

#if !defined(m_STATIC) && defined(_WIN32)
#   define m_FIMPORT __declspec(dllimport)
#   define m_FEXPORT __declspec(dllexport)
#   define m_DIMPORT m_FIMPORT
#   define m_DEXPORT m_FEXPORT
#else
#   define m_FIMPORT extern
#   define m_FEXPORT
#   define m_DIMPORT m_FIMPORT
#   define m_DEXPORT
#endif

#if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && defined(__ELF__)
#   define m_HFIMPORT __attribute__((visibility("hidden"))) extern
#   define m_HFEXPORT static
#   define m_HDIMPORT m_HFIMPORT
#   define m_HDEXPORT m_HFEXPORT
#else
#   define m_HFIMPORT extern
#   define m_HFEXPORT static
#   define m_HDIMPORT m_HFIMPORT
#   define m_HDEXPORT m_HFEXPORT
#endif

#if defined(m_BUILDING)
#   define m_API m_FEXPORT
#   define m_DATA m_DEXPORT
#   define m_IAPI m_HFEXPORT
#   define m_IDATA m_HFEXPORT
#else
#   define m_API m_FIMPORT
#   define m_DATA m_DIMPORT
#   define m_IAPI m_HFIMPORT
#   define m_IDATA m_HFIMPORT
#endif


#ifndef m_USERAPI
#   ifdef m_USERBUILDING
#      define m_USERAPI m_FEXPORT
#   else
#      define m_USERAPI m_FIMPORT
#   endif
#endif

#ifndef m_USERDATA
#   ifdef m_USERBUILDING
#      define m_USERDATA m_DEXPORT
#   else
#      define m_USERDATA m_DIMPORT
#   endif
#endif

#ifndef m_USERIAPI
#   ifdef m_USERBUILDING
#      define m_USERIAPI m_HFEXPORT
#   else
#      define m_USERIAPI m_HFIMPORT
#   endif
#endif

#ifndef m_USERIDATA
#   ifdef m_USERBUILDING
#      define m_USERIDATA m_HDEXPORT
#   else
#      define m_USERIDATA m_HDIMPORT
#   endif
#endif

#ifdef _MSC_VER
#  define m_PACKED(body) \
    __pragma(pack(push, 1)) body __pragma(pack(pop))
#elif defined(__GNUC__)
#  define m_PACKED(body) \
    name __attribute__((packed))
#endif

#else

#define m_RELEASENAME

#define m_USERAPI
#define m_USERDATA
#define m_USERIAPI
#define m_USERIDATA

#define m_API
#define m_DATA
#define m_IAPI
#define m_IDATA

#define m_RESTRICT
#define m_FEXPORT
#define m_FIMPORT
#define m_DEXPORT
#define m_DIMPORT
#define m_HFEXPORT
#define m_HFIMPORT
#define m_HDEXPORT
#define m_HDIMPORT
#define m_PACKED(body)

#endif /* m_BUILDING */


/*==============================================================================
 * [[[   B A S E    ]]]
 * Basic definitions and macros.
 */


typedef enum m_EErr m_EErr;
typedef struct m_Api m_Api;
typedef struct m_Obj m_Obj;

struct m_Api {
    const m_Api* baseapi;
    const char*  apiname;
    size_t       objsize;
};

struct m_Obj {
    m_Api* objapi;
};

#define m(S, A)    S ## __ ## A
#define m_t(S, A)  m(S, A)
#define m_type     m_t
#define m_p(S, A)  m(S, A) ## __ptr
#define m_ptr      m_p
#define m_a(S, A)  m(S, A) ## __api
#define m_api      m_a
#define m_f(S,A,n) m(S, A) ## _ ## n
#define m_function m_f
#define m_fp(S, A) m(S, A) ## __fnproto
#define m_fnproto  m_fn

#define m_ki(S,A,i) m(S, A) ## __key ## i
#define m_keytypei  m_ki
#define m_vi(S,A,i) m(S, A) ## __val ## i
#define m_valtypei  m_vi
#define m_k(S, A)   m_ki(S, A, 0)
#define m_keytype   m_k
#define m_v(S, A)   m_vi(S, A, 0)
#define m_valtype   m_v
#define m_i(S, A)   m(S, A) ## __iter
#define m_iter      m_i
#define m_ip(S, A)  m(S, A) ## __iterptr
#define m_iterptr   m_ip

#define m_DECT(S, A) m(S, A) ## _DECT
#define m_DECS(S, A) m(S, A) ## _DECS
#define m_DECL(S, A) m_DECT(S, A); m_DECS
#define m_DEFN(S, A) m(S, A) ## _DEFN
#define m_IMPL(S, A) DECL(S, A); m_DEFN

#define m_FP(S, A, n, r, a) typedef r (* m_fp(S, A, N)) a
#define m_FNPROTO           m_FP

#define m_DECLTYPES(S, A) \
    typedef struct m_t(S, A)  m(S, A); \
    typedef m_p(S, A)*        m_p(S, A); \
    typedef struct m_a(S, A)  m_a(S, A)


#endif /* MCONFIG_H_ */
