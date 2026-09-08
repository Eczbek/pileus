#ifndef PL_FEATURE_H
#define PL_FEATURE_H

#ifdef __GNUC__
 #define pl_feature_gcc 1
#else
 #define pl_feature_gcc 0
#endif

#ifdef __clang__
 #define pl_feature_clang 1
#else
 #define pl_feature_clang 0
#endif

#ifdef INT8_MAX
 #define pl_feature_int8 1
#else
 #define pl_feature_int8 0
#endif

#ifdef INT16_MAX
 #define pl_feature_int16 1
#else
 #define pl_feature_int16 0
#endif

#ifdef INT32_MAX
 #define pl_feature_int32 1
#else
 #define pl_feature_int32 0
#endif

#ifdef INT64_MAX
 #define pl_feature_int64 1
#else
 #define pl_feature_int64 0
#endif

#ifdef __SIZEOF_INT128__
 #define pl_feature_int128 1
__extension__ typedef unsigned __int128 pl_uint128_t;
__extension__ typedef __int128 pl_int128_t;
#else
 #define pl_feature_int128 0
#endif

#ifdef INTPTR_MAX
 #define pl_feature_intptr 1
#else
 #define pl_feature_intptr 0
#endif

#endif
