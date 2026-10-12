#ifndef PL_STATIC_ASSERT_H
#define PL_STATIC_ASSERT_H

#ifdef __clang__
 #define pl_static_assert(...) ((void)(struct{static_assert(__VA_ARGS__);int defined;}){})
#elifdef __GNUC__
 #define pl_static_assert(...) ((typeof(static_assert(__VA_ARGS__)))0)
#else
 #define pl_static_assert(...) static_assert(__VA_ARGS__)
#endif

#endif
