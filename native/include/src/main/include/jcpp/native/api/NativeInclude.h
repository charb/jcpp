#ifndef JCPP_NATIVE_INCLUDE
#define JCPP_NATIVE_INCLUDE

//~ -------------------------------------------------
//~ define JCPP_EXPORT
//~ -------------------------------------------------

#if defined (__GNUC__) && defined(__unix__)
#define JCPP_EXPORT __attribute__ ((__visibility__("default")))
#define JCPP_IMPORT 
#elif defined (WIN32)
#define JCPP_EXPORT __declspec(dllexport)
#define JCPP_IMPORT __declspec(dllimport)
#else
#define JCPP_EXPORT
#define JCPP_IMPORT
#endif

//~ -------------------------------------------------
//~ define null
//~ -------------------------------------------------

#define null 0

//~ -------------------------------------------------
//~ define primitives
//~ -------------------------------------------------

typedef int jint;
typedef short jshort;
typedef long long jlong;
typedef char jbyte;
typedef float jfloat;
typedef double jdouble;
typedef unsigned short jchar;
typedef bool jbool;

//~ -------------------------------------------------
//~ Primitives Limits
//~ -------------------------------------------------

#define JINT_MAX 0x7FFFFFFF
#define JINT_MIN 0x80000000

#define JSHORT_MAX 0x7FFF
#define JSHORT_MIN 0x8000

#define JLONG_MAX 0x7FFFFFFFFFFFFFFFLL
#define JLONG_MIN 0x8000000000000000LL

#define JBYTE_MAX 0x7F
#define JBYTE_MIN 0x80

#define JCHAR_MAX 0xFFFF
#define JCHAR_MIN 0x0000

#define JDOUBLE_MAX 1.7976931348623158e+308;
#define JDOUBLE_MIN -1.7976931348623158e+308;
#define JDOUBLE_MIN_POSITIVE 4.9e-324;
#define JDOUBLE_MIN_NEGATIVE -4.9e-324;

#define JFLOAT_MAX 3.402823466e+38F
#define JFLOAT_MIN -3.402823466e+38F
#define JFLOAT_MIN_POSITIVE 1.4e-45F;
#define JFLOAT_MIN_NEGATIVE -1.4e-45F;

#if defined(Linux)
//~ -------------------------------------------------
//~ Signals
//~ -------------------------------------------------
#define SIG_SUSPEND SIGRTMAX-1
#define SIG_RESUME SIGRTMAX

#endif

#endif
