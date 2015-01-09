#ifndef ECHO
#define ECHO

//~ -------------------------------------------------
//~ define JCPP_EXPORT
//~ -------------------------------------------------

#if defined (__GNUC__) && defined(__unix__)
#define JCPP_EXPORT __attribute__ ((__visibility__("default")))
#elif defined (WIN32)
#define JCPP_EXPORT __declspec(dllexport)
#else
#define JCPP_EXPORT
#endif

JCPP_EXPORT char* echo(char* text);

#endif
