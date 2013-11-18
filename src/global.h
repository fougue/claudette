#ifndef FOUGCOLDET_GLOBAL_H
#define FOUGCOLDET_GLOBAL_H

#ifndef FOUG_DECL_EXPORT
 #if defined(WIN64) || defined(_WIN64) || defined(__WIN64__) \
     || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
 # define FOUG_DECL_EXPORT __declspec(dllexport)
 # define FOUG_DECL_IMPORT __declspec(dllimport)
 #else
 # define FOUG_DECL_EXPORT
 # define FOUG_DECL_IMPORT
 #endif /* WIN */
#endif /* !FOUG_DECL_EXPORT */

#ifdef FOUGCOLDET_LIB_DLL
# ifdef FOUGCOLDET_LIB_MAKE_DLL
#  define FOUGCOLDET_LIB_EXPORT FOUG_DECL_EXPORT
# else
#  define FOUGCOLDET_LIB_EXPORT FOUG_DECL_IMPORT
# endif /* FOUGCOLDET_LIB_MAKE_DLL */
#else
# define FOUGCOLDET_LIB_EXPORT
#endif /* FOUGCOLDET_LIB_DLL */

#endif /* FOUGCOLDET_GLOBAL_H */
