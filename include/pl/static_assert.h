#ifndef PL_STATIC_ASSERT_H
#define PL_STATIC_ASSERT_H

#ifndef __clang__
 #ifdef __GNUC__
  #pragma GCC diagnostic ignored "-Wunused-value" // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=127192
 #endif
 #define pl_static_assert(...) static_assert(__VA_ARGS__)
#else
 #define pl_static_assert(...) ((void)(struct { static_assert(__VA_ARGS__); int defined; }){})
#endif

#endif
