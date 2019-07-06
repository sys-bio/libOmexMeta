# ifndef SEMSIM_PREPROC_H_
# define SEMSIM_PREPROC_H_

#if defined _WIN32 || defined __CYGWIN__
  #ifdef SEMSIM_INTERNAL_BUILD
    #ifdef __GNUC__
      #define SEMSIM_PUBLIC __attribute__ ((dllexport))
    #else
      #define SEMSIM_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define SEMSIM_PUBLIC __attribute__ ((dllimport))
    #else
      #define SEMSIM_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define SEMSIM_LOCAL
#else
  #if __GNUC__ >= 4 && !defined SWIG
    #define SEMSIM_PUBLIC  __attribute__ ((visibility ("default")))
    #define SEMSIM_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define SEMSIM_PUBLIC
    #define SEMSIM_LOCAL
  #endif
#endif

// C++11 features
# if __cplusplus >= 201103L
  #define SEMSIM_CONSTEXPR constexpr
  #define SEMSIM_TR1_NAMESPACE_QUAL std::
# else
  #define SEMSIM_CONSTEXPR const
  #define SEMSIM_TR1_NAMESPACE_QUAL std::tr1::
# endif

# endif
