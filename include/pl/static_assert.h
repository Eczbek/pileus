#ifndef PL_STATIC_ASSERT_H
#define PL_STATIC_ASSERT_H

#ifndef __clang__
 #define pl_static_assert(...) static_assert(__VA_ARGS__)
#else
 #define pl_static_assert(...) ((void)(struct { static_assert(__VA_ARGS__); int defined; }){})
#endif

#endif
