#ifndef PL_META_H
#define PL_META_H

#include "./feature.h"
#include "./preproc.h"
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <uchar.h>
#include <wchar.h>

// Evaluates to whether the arguments' types are compatible.
#define pl_is_same(lhs, /*rhs*/...) _Generic(typeof(lhs),typeof(__VA_ARGS__):1,default:0)

// Evaluates to whether the arguments' types are compatible, ignoring qualifiers.
#define pl_is_same_unqual(lhs, /*rhs*/...) _Generic(typeof_unqual(lhs),typeof_unqual(__VA_ARGS__):1,default:0)

// Accepts a condition expression and two other expressions.
// The condition must be constant and integer-like.
// If the condition is truthy, evaluates to the second expression.
// Otherwise, evaluates to the third expression.
#define pl_choose(cond, then, /*else*/...) _Generic(int[1+!(cond)],int[1]:(then),default:(__VA_ARGS__))

// Accepts a condition expression and two other types or expressions.
// The condition must be constant and integer-like.
// If the condition is truthy, evaluates to the second argument's type.
// Otherwise, evaluates to the third argument's type.
#define pl_choose_type(cond, then, /*else*/...) typeof(pl_choose((cond),pl_fake(then),pl_fake(__VA_ARGS__)))

// Evaluates to an lvalue expression of the argument's type.
// Must not be used in evaluated contexts.
#define pl_fake(/*type*/...) (*(typeof(__VA_ARGS__)*)0)

// Evaluates to an lvalue expression of the argument's type, ignoring qualifiers.
// Must not be used in evaluated contexts.
#define pl_fake_unqual(/*type*/...) (*(typeof_unqual(__VA_ARGS__)*)0)

#ifdef __GNUC__
 // Evaluates to whether the argument's type is a pointer type.
 #ifndef __clang__
  #define pl_is_pointer(/*type*/...) (__builtin_classify_type(typeof(__VA_ARGS__))==5)
 #else
  #define pl_is_pointer(/*type*/...) (__builtin_classify_type(pl_fake(__VA_ARGS__))==5&&!pl_is_function_or_array(__VA_ARGS__))
 #endif
#endif

// Evaluates to whether the argument's type is a function type.
// Function pointer types are not considered to be function types.
#if defined(__GNUC__) && !defined(__clang__)
 #define pl_is_function(/*type*/...) (__builtin_classify_type(typeof(__VA_ARGS__))==10)
#else
 #define pl_is_function(/*type*/...) _Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:1,default:0)
#endif

// Evaluates to whether the argument's type is an array type.
#if defined(__GNUC__) && !defined(__clang__)
 #define pl_is_array(/*type*/...) (__builtin_classify_type(typeof(__VA_ARGS__))==14)
#else
 #define pl_is_array(/*type*/...) _Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:!pl_is_decayed(__VA_ARGS__))
#endif

// Evaluates to whether the argument's type is a function or array type.
#if defined(__GNUC__) && !defined(__clang__)
 #define pl_is_function_or_array(/*type*/...) (1&34816l>>(1+__builtin_classify_type(typeof(__VA_ARGS__))))
#else
 #define pl_is_function_or_array(/*type*/...) _Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:1,default:!pl_is_decayed(__VA_ARGS__))
#endif

// Evaluates to whether the argument's type is a sized array type.
#define pl_is_sized_array(/*type*/...) _Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):0,default:!pl_is_unsized_array(__VA_ARGS__)))

// Evaluates to whether the argument's type is an unsized array type.
#define pl_is_unsized_array(/*type*/...) _Generic(typeof(__VA_ARGS__),typeof(*pl_choose(pl_is_array(__VA_ARGS__),pl_fake(__VA_ARGS__),""))[1]:_Generic(typeof(__VA_ARGS__),typeof(*pl_choose(pl_is_array(__VA_ARGS__),pl_fake(__VA_ARGS__),""))[2]:1,default:0),default:0)

// If the argument's type is a sized array type, evaluates to the array's size.
// Otherwise, evaluates to zero.
#define pl_extent(/*type*/...) (sizeof pl_choose(pl_is_sized_array(__VA_ARGS__),pl_fake(__VA_ARGS__),"")/sizeof*pl_choose(pl_is_sized_array(__VA_ARGS__),pl_fake(__VA_ARGS__),&""))

#ifdef __GNUC__
 // If the argument's type is a pointer type, evaluates to the pointee type.
 // Otherwise, evaluates to the original type.
 #define pl_drop_pointer(/*type*/...) pl_choose_type(pl_is_pointer(__VA_ARGS__),*pl_fake(pl_choose_type(pl_is_pointer(__VA_ARGS__),typeof(__VA_ARGS__),"")),__VA_ARGS__)
#endif

// If the argument's type is an array type, evaluates to the array's value type.
// Otherwise, evaluates to the original type.
#define pl_drop_extent(/*type*/...) pl_choose_type(pl_is_array(__VA_ARGS__),*pl_fake(pl_choose_type(pl_is_array(__VA_ARGS__),typeof(__VA_ARGS__),"")),__VA_ARGS__)

// Evaluates to the argument's type, decayed.
// Integer-like types are not promoted.
#define pl_decay(/*type*/...) pl_choose_type(pl_int_width(__VA_ARGS__)-1<INT_WIDTH-1,typeof(__VA_ARGS__),0?pl_fake(__VA_ARGS__):pl_fake(__VA_ARGS__))

// Evaluates to whether the argument's type is decayed.
#define pl_is_decayed(/*type*/...) _Generic(typeof_unqual(__VA_ARGS__),pl_decay(__VA_ARGS__):1,default:0)

// Evaluates to whether the argument's type is a void type.
#define pl_is_void(/*type*/...) _Generic(typeof_unqual(__VA_ARGS__),void:1,default:0)

// Evaluates to whether the argument's type is an integer type.
#ifdef __GNUC__
 // Detects _BitInt and extended integer types.
 #define pl_is_int(/*type*/...) (1&524324l>>(1+__builtin_classify_type(pl_fake(__VA_ARGS__))))
#else
 #define pl_is_int(/*type*/...) (!!pl_int_width(__VA_ARGS__))
#endif

// Evaluates to whether the argument's type is an unsigned integer type.
// Optionally upports _BitInt and extended integer types.
#define pl_is_unsigned_int(/*type*/...) ((pl_choose_type(pl_is_int(__VA_ARGS__),typeof(__VA_ARGS__),0))-1>0)

// Evaluates to whether the argument's type is a signed integer type.
// Optionally upports _BitInt and extended integer types.
#define pl_is_signed_int(/*type*/...) ((pl_choose_type(pl_is_int(__VA_ARGS__),typeof(__VA_ARGS__),0u))-1<0)

// Evaluates to the unsigned counterpart of a signed integer type, if it exists.
// Otherwise, evaluates to the argument's type without qualifiers.
// Optionally supports _BitInt.
#define pl_make_unsigned_int(/*int_type*/...) typeof(_Generic(typeof_unqual(__VA_ARGS__),signed char:(unsigned char)0,short:(unsigned short)0,int:0u,long:0ul,long long:0ull,char:(unsigned char)0,default:_Generic(typeof_unqual(__VA_ARGS__),PL_IF(pl_feature_int8)(int8_t:(uint8_t)0,)()PL_IF(pl_feature_int16)(int16_t:(uint16_t)0,)()PL_IF(pl_feature_int32)(int32_t:(uint32_t)0,)()PL_IF(pl_feature_int64)(int64_t:(uint64_t)0,)()PL_IF(pl_feature_int128)(pl_int128_t:(pl_uint128_t)0,)()default:_Generic(typeof_unqual(__VA_ARGS__),intmax_t:(uintmax_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),PL_IF(pl_feature_intptr)(intptr_t:(uintptr_t)0,)()default:_Generic(typeof_unqual(__VA_ARGS__),int_least8_t:(uint_least8_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),int_least16_t:(uint_least16_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),int_least32_t:(uint_least32_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),int_least64_t:(uint_least64_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),int_fast8_t:(uint_fast8_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),int_fast16_t:(uint_fast16_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),int_fast32_t:(uint_fast32_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),int_fast64_t:(uint_fast64_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),PL_IF(pl_feature_gcc)(PL_IF(pl_feature_clang)()(_BitInt(pl_int_width(__VA_ARGS__)+!pl_is_int(__VA_ARGS__)):(unsigned _BitInt(pl_int_width(__VA_ARGS__)+!pl_is_int(__VA_ARGS__)))0,))()default:pl_fake_unqual(__VA_ARGS__)))))))))))))))

// Evaluates to the signed counterpart of an unsigned integer type, if it exists.
// Otherwise, evaluates to the argument's type without qualifiers.
// Optionally supports _BitInt.
#define pl_make_signed_int(/*int_type*/...) typeof(_Generic(typeof_unqual(__VA_ARGS__),unsigned char:(signed char)0,unsigned short:(short)0,typeof(0u):0,typeof(0ul):0l,typeof(0ull):0ll,char:(signed char)0,default:_Generic(typeof_unqual(__VA_ARGS__),PL_IF(pl_feature_int8)(uint8_t:(int8_t)0,)()PL_IF(pl_feature_int16)(uint16_t:(int16_t)0,)()PL_IF(pl_feature_int32)(uint32_t:(int32_t)0,)()PL_IF(pl_feature_int64)(uint64_t:(int64_t)0,)()PL_IF(pl_feature_int128)(pl_uint128_t:(pl_int128_t)0,)()default:_Generic(typeof_unqual(__VA_ARGS__),uintmax_t:(intmax_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),PL_IF(pl_feature_intptr)(uintptr_t:(intptr_t)0,)()default:_Generic(typeof_unqual(__VA_ARGS__),uint_least8_t:(int_least8_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),uint_least16_t:(int_least16_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),uint_least32_t:(int_least32_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),uint_least64_t:(int_least64_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),uint_fast8_t:(int_fast8_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),uint_fast16_t:(int_fast16_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),uint_fast32_t:(int_fast32_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),uint_fast64_t:(int_fast64_t)0,default:_Generic(typeof_unqual(__VA_ARGS__),PL_IF(pl_feature_gcc)(PL_IF(pl_feature_clang)()(unsigned _BitInt(pl_int_width(__VA_ARGS__)+!pl_is_int(__VA_ARGS__)):(_BitInt(pl_int_width(__VA_ARGS__)+!pl_is_int(__VA_ARGS__)))0,))()default:pl_fake_unqual(__VA_ARGS__)))))))))))))))

// Evaluates to the width of an integer type.
// If the argument's type is not an integer type, evaluates to zero.
#if defined(__GNUC__) && !defined(__clang__)
 // Supports _BitInt and extended integer types.
 #define pl_int_width(/*int_type*/...) (pl_is_int(__VA_ARGS__)?(size_t)__builtin_popcountg((unsigned _BitInt(BITINT_MAXWIDTH))__extension__ _Maxof(pl_choose_type(pl_is_int(__VA_ARGS__),typeof(__VA_ARGS__),0)))+pl_is_signed_int(__VA_ARGS__):0)
#else
 #define pl_int_width(/*int_type*/...) ((size_t)_Generic(typeof_unqual(__VA_ARGS__),unsigned char:CHAR_BIT,unsigned short:SHRT_WIDTH,typeof(0u):INT_WIDTH,typeof(0ul):LONG_WIDTH,typeof(0ull):LLONG_WIDTH,signed char:CHAR_BIT,short:SHRT_WIDTH,int:INT_WIDTH,long:LONG_WIDTH,long long:LLONG_WIDTH,char:CHAR_BIT,bool:1,default:_Generic(typeof_unqual(__VA_ARGS__),PL_IF(pl_feature_int8)(uint8_t:8,int8_t:8,)()PL_IF(pl_feature_int16)(uint16_t:16,int16_t:16,)()PL_IF(pl_feature_int32)(uint32_t:32,int32_t:32,)()PL_IF(pl_feature_int64)(uint64_t:64,int64_t:64,)()PL_IF(pl_feature_int128)(pl_uint128_t:128,pl_int128_t:128,)()default:_Generic(typeof_unqual(__VA_ARGS__),size_t:SIZE_WIDTH,ptrdiff_t:PTRDIFF_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),uintmax_t:INTMAX_WIDTH,intmax_t:INTMAX_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),PL_IF(pl_feature_intptr)(uintptr_t:INTPTR_WIDTH,intptr_t:INTPTR_WIDTH,)()default:_Generic(typeof_unqual(__VA_ARGS__),uint_least8_t:INT_LEAST8_WIDTH,int_least8_t:INT_LEAST8_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),uint_least16_t:INT_LEAST16_WIDTH,int_least16_t:INT_LEAST16_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),uint_least32_t:INT_LEAST32_WIDTH,int_least32_t:INT_LEAST32_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),uint_least64_t:INT_LEAST64_WIDTH,int_least64_t:INT_LEAST64_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),uint_fast8_t:INT_FAST8_WIDTH,int_fast8_t:INT_FAST8_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),uint_fast16_t:INT_FAST16_WIDTH,int_fast16_t:INT_FAST16_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),uint_fast32_t:INT_FAST32_WIDTH,int_fast32_t:INT_FAST32_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),uint_fast64_t:INT_FAST64_WIDTH,int_fast64_t:INT_FAST64_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),wchar_t:WCHAR_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),wint_t:WINT_WIDTH,default:_Generic(typeof_unqual(__VA_ARGS__),sig_atomic_t:SIG_ATOMIC_WIDTH,default:0)))))))))))))))))
#endif

// Evaluates to whether the argument's type is a floating-point type.
#ifdef __GNUC__
 // Supports extended floating-point types.
 #define pl_is_float(/*type*/...) (__builtin_classify_type(pl_fake(__VA_ARGS__))==8&&!pl_is_decimal_float(__VA_ARGS__))
#else
 #define pl_is_float(/*type*/...) _Generic(typeof_unqual(__VA_ARGS__),float:1,double:1,long double:1,default:0)
#endif

// Evaluates to whether the argument's type is a decimal floating-point type.
#ifdef __STDC_IEC_60559_DFP__
 #define pl_is_decimal_float(/*type*/...) _Generic(typeof_unqual(__VA_ARGS__),_Decimal32:1,_Decimal64:1,_Decimal128:1,default:0)
#else
 #define pl_is_decimal_float(/*type*/...) 0
#endif

// Evaluates to whether the argument's type has a const qualifier.
#define pl_is_const(/*type*/...) _Generic(typeof(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof(__VA_ARGS__))const:1,default:0)

// Evaluates to whether the argument's type has a volatile qualifier.
#define pl_is_volatile(/*type*/...) _Generic(typeof(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof(__VA_ARGS__))volatile:1,default:0)

// Evaluates to whether the argument's type has const and volatile qualifiers.
#define pl_is_const_volatile(/*type*/...) _Generic(typeof(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof(__VA_ARGS__))const volatile:1,default:0)

// Evaluates to whether the argument's type has an _Atomic qualifier.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_is_atomic(/*type*/...) _Generic(typeof(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof(__VA_ARGS__))_Atomic:1,default:0)
 #else
  #define pl_is_atomic(/*type*/...) _Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile _Atomic:1,default:0)
 #endif
#else
 #define pl_is_atomic(/*type*/...) 0
#endif

// Evaluates to whether the argument's type has const and _Atomic qualifiers.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_is_const_atomic(/*type*/...) _Generic(typeof(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof(__VA_ARGS__))const _Atomic:1,default:0)
 #else
  #define pl_is_const_atomic(/*type*/...) _Generic(pl_add_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile _Atomic:1,default:0)
 #endif
#else
 #define pl_is_const_atomic(/*type*/...) 0
#endif

// Evaluates to whether the argument's type has volatile and _Atomic qualifiers.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_is_volatile_atomic(/*type*/...) _Generic(typeof(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof(__VA_ARGS__))volatile _Atomic:1,default:0)
 #else
  #define pl_is_volatile_atomic(/*type*/...) _Generic(pl_add_const(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile _Atomic:1,default:0)
 #endif
#else
 #define pl_is_volatile_atomic(/*type*/...) 0
#endif

// Evaluates to whether the argument's type has const, volatile, and _Atomic qualifiers.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_is_const_volatile_atomic(/*type*/...) _Generic(typeof(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof(__VA_ARGS__))const volatile _Atomic:1,default:0)
 #else
  #define pl_is_const_volatile_atomic(/*type*/...) _Generic(typeof(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile _Atomic:1,default:0)
 #endif
#else
 #define pl_is_const_volatile_atomic(/*type*/...) 0
#endif

// Evaluates to whether the argument's type has a restrict qualifier.
#ifdef __GNUC__
 #define pl_is_restrict(/*type*/...) _Generic(typeof(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),typeof(__VA_ARGS__),int*)restrict:1,default:0)
#elif defined(__clang__) || defined(__STDC_NO_ATOMICS__)
 #define pl_is_restrict(/*type*/...) _Generic(pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof(__VA_ARGS__))const volatile,pl_choose_type
  (pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const volatile:0,default:!pl_is_atomic(__VA_ARGS__))
#else
 #define pl_is_restrict(/*type*/...) _Generic(pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof(__VA_ARGS__))const volatile _Atomic,pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const volatile _Atomic:0,default:1)
#endif

// Evaluates to whether the argument's type has const and restrict qualifiers.
#define pl_is_const_restrict(/*type*/...) (pl_is_const(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))

// Evaluates to whether the argument's type has volatile and restrict qualifiers.
#define pl_is_volatile_restrict(/*type*/...) (pl_is_volatile(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))

// Evaluates to whether the argument's type has const, volatile, and restrict qualifiers.
#define pl_is_const_volatile_restrict(/*type*/...) (pl_is_const_volatile(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))

// Evaluates to whether the argument's type has _Atomic and restrict qualifiers.
#if !defined(__STDC_NO_ATOMICS__) && !defined(__clang__)
 #define pl_is_atomic_restrict(/*type*/...) (pl_is_atomic(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))
#else
 #define pl_is_atomic_restrict(/*type*/...) 0
#endif

// Evaluates to whether the argument's type has const, _Atomic, and restrict qualifiers.
#if !defined(__STDC_NO_ATOMICS__) && !defined(__clang__)
 #define pl_is_const_atomic_restrict(/*type*/...) (pl_is_const_atomic(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))
#else
 #define pl_is_const_atomic_restrict(/*type*/...) 0
#endif

// Evaluates to whether the argument's type has volatile, _Atomic, and restrict qualifiers.
#if !defined(__STDC_NO_ATOMICS__) && !defined(__clang__)
 #define pl_is_volatile_atomic_restrict(/*type*/...) (pl_is_volatile_atomic(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))
#else
 #define pl_is_volatile_atomic_restrict(/*type*/...) 0
#endif

// Evaluates to whether the argument's type has const, volatile, _Atomic, and restrict qualifiers.
#if !defined(__STDC_NO_ATOMICS__) && !defined(__clang__)
 #define pl_is_const_volatile_atomic_restrict(/*type*/...) (pl_is_const_volatile_atomic(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))
#else
 #define pl_is_const_volatile_atomic_restrict(/*type*/...) 0
#endif

// Evaluates to the argument's type with a const qualifier.
// If the argument's type is a function type, it is unchanged.
#define pl_add_const(/*type*/...) pl_choose_type(pl_is_function(__VA_ARGS__),typeof(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof(__VA_ARGS__))const)

// Evaluates to the argument's type with a volatile qualifier.
// If the argument's type is a function type, it is unchanged.
#define pl_add_volatile(/*type*/...) pl_choose_type(pl_is_function(__VA_ARGS__),typeof(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof(__VA_ARGS__))volatile)

// Evaluates to the argument's type with const and volatile qualifiers.
// If the argument's type is a function type, it is unchanged.
#define pl_add_const_volatile(/*type*/...) pl_choose_type(pl_is_function(__VA_ARGS__),typeof(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof(__VA_ARGS__))const volatile)

// Evaluates to the argument's type with an _Atomic qualifier.
// If the argument's type is a function or array type, it is unchanged.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_add_atomic(/*type*/...) pl_choose_type(pl_is_function_or_array(__VA_ARGS__),typeof(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof(__VA_ARGS__))_Atomic)
 #else
  // If the argument's type is void or has a restrict qualifier, _Atomic is not applied.
  #define pl_add_atomic(/*type*/...) typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(__VA_ARGS__),default:0))_Atomic),default:pl_fake(__VA_ARGS__)))
 #endif
#else
 #define pl_add_atomic(/*type*/...) typeof(__VA_ARGS__)
#endif

// Evaluates to the argument's type with const and _Atomic qualifiers.
// If the argument's type is a function or array type, it is unchanged.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_add_const_atomic(/*type*/...) pl_choose_type(pl_is_function_or_array(__VA_ARGS__),typeof(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof(__VA_ARGS__))const _Atomic)
 #else
  // If the argument's type is void or has a restrict qualifier, _Atomic is not applied.
  #define pl_add_const_atomic(/*type*/...) typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(__VA_ARGS__),default:0))const _Atomic),default:pl_fake(pl_add_const(__VA_ARGS__))))
 #endif
#else
 #define pl_add_const_atomic(/*type*/...) pl_add_const(__VA_ARGS__)
#endif

// Evaluates to the argument's type with volatile and _Atomic qualifiers.
// If the argument's type is a function or array type, it is unchanged.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_add_volatile_atomic(/*type*/...) pl_choose_type(pl_is_function_or_array(__VA_ARGS__),typeof(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof(__VA_ARGS__))volatile _Atomic)
 #else
  // If the argument's type is void or has a restrict qualifier, _Atomic is not applied.
  #define pl_add_volatile_atomic(/*type*/...) typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(__VA_ARGS__),default:0))volatile _Atomic),default:pl_fake(pl_add_volatile(__VA_ARGS__))))
 #endif
#else
 #define pl_add_volatile_atomic(/*type*/...) pl_add_volatile(__VA_ARGS__)
#endif

// Evaluates to the argument's type with const, volatile, and _Atomic qualifiers.
// If the argument's type is a function or array type, it is unchanged.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_add_const_volatile_atomic(/*type*/...) pl_choose_type(pl_is_function_or_array(__VA_ARGS__),typeof(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof(__VA_ARGS__))const volatile _Atomic)
 #else
  // If the argument's type is void or has a restrict qualifier, _Atomic is not applied.
  #define pl_add_const_volatile_atomic(/*type*/...) typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(__VA_ARGS__),default:0))const volatile _Atomic),default:pl_fake(pl_add_const_volatile(__VA_ARGS__))))
 #endif
#else
 #define pl_add_const_volatile_atomic(/*type*/...) pl_add_const_volatile(__VA_ARGS__)
#endif

#ifdef __GNUC__
 // Evaluates to the argument's type with a restrict qualifier.
 // If the argument's type is not a pointer, restrict is not applied.
 #define pl_add_restrict(/*type*/...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),typeof(__VA_ARGS__),int*)restrict,__VA_ARGS__)
#endif

#ifdef __GNUC__
 // Evaluates to the argument's type with const and restrict qualifiers.
 // If the argument's type is a function or array type, const is not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #define pl_add_const_restrict(/*type*/...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_const(__VA_ARGS__),int*)restrict,pl_add_const(__VA_ARGS__))
#endif

#ifdef __GNUC__
 // Evaluates to the argument's type with volatile and restrict qualifiers.
 // If the argument's type is a function or array type, volatile is not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #define pl_add_volatile_restrict(/*type*/...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_volatile(__VA_ARGS__),int*)restrict,pl_add_volatile(__VA_ARGS__))
#endif

#ifdef __GNUC__
 // Evaluates to the argument's type with const, volatile, and restrict qualifiers.
 // If the argument's type is a function or array type, const and volatile are not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #define pl_add_const_volatile_restrict(/*type*/...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_const_volatile(__VA_ARGS__),int*)restrict,pl_add_const_volatile(__VA_ARGS__))
#endif

#if defined(__GNUC__) && !defined(__clang__)
 // Evaluates to the argument's type with _Atomic and restrict qualifiers.
 // If the argument's type is a function or array type, _Atomic is not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #ifndef __STDC_NO_ATOMICS__
  #define pl_add_atomic_restrict(/*type*/...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_atomic(__VA_ARGS__),int*)restrict,pl_add_atomic(__VA_ARGS__))
 #else
  #define pl_add_atomic_restrict(/*type*/...) pl_add_restrict(__VA_ARGS__)
 #endif
#endif

#if defined(__GNUC__) && !defined(__clang__)
 // Evaluates to the argument's type with const, _Atomic, and restrict qualifiers.
 // If the argument's type is a function or array type, const and _Atomic are not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #ifndef __STDC_NO_ATOMICS__
  #define pl_add_const_atomic_restrict(/*type*/...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_const_atomic(__VA_ARGS__),int*)restrict,pl_add_const_atomic(__VA_ARGS__))
 #else
  #define pl_add_const_atomic_restrict(/*type*/...) pl_add_const_restrict(__VA_ARGS__)
 #endif
#endif

#if defined(__GNUC__) && !defined(__clang__)
 // Evaluates to the argument's type with volatile, _Atomic, and restrict qualifiers.
 // If the argument's type is a function or array type, volatile and _Atomic are not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #ifndef __STDC_NO_ATOMICS__
  #define pl_add_volatile_atomic_restrict(/*type*/...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_volatile_atomic(__VA_ARGS__),int*)restrict,pl_add_volatile_atomic(__VA_ARGS__))
 #else
  #define pl_add_volatile_atomic_restrict(/*type*/...) pl_add_volatile_restrict(__VA_ARGS__)
 #endif
#endif

#if defined(__GNUC__) && !defined(__clang__)
 // Evaluates to the argument's type with const, volatile, _Atomic, and restrict qualifiers.
 // If the argument's type is a function or array type, const and _Atomic are not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #ifndef __STDC_NO_ATOMICS__
  #define pl_add_const_volatile_atomic_restrict(/*type*/...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_const_volatile_atomic(__VA_ARGS__),int*)restrict,pl_add_const_volatile_atomic(__VA_ARGS__))
 #else
  #define pl_add_const_volatile_atomic_restrict(/*type*/...) pl_add_const_volatile_restrict(__VA_ARGS__)
 #endif
#endif

// Evaluates to the argument's type without a const qualifier.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_drop_const(/*type*/...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_const_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile _Atomic,pl_choose_type(pl_is_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,pl_choose_type(pl_is_const_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,pl_choose_type(pl_is_const(__VA_ARGS__),typeof_unqual(__VA_ARGS__),__VA_ARGS__)))),int*)restrict,pl_choose_type(pl_is_const_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile _Atomic,pl_choose_type(pl_is_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,pl_choose_type(pl_is_const_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,pl_choose_type(pl_is_const(__VA_ARGS__),typeof_unqual(__VA_ARGS__),__VA_ARGS__)))))
 #else
  #define pl_drop_const(/*type*/...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,pl_choose_type(pl_is_const(__VA_ARGS__),typeof_unqual(__VA_ARGS__),__VA_ARGS__)),int*)restrict,pl_choose_type(pl_is_const_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile _Atomic,pl_choose_type(pl_is_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,pl_choose_type(pl_is_const_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,pl_choose_type(pl_is_const(__VA_ARGS__),typeof_unqual(__VA_ARGS__),__VA_ARGS__)))))
 #endif
#else
 #define pl_drop_const(/*type*/...) pl_drop_const_atomic(__VA_ARGS__)
#endif

// Evaluates to the argument's type without a volatile qualifier.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_drop_volatile(/*type*/...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_const_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const _Atomic,pl_choose_type(pl_is_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,pl_choose_type(pl_is_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,pl_choose_type(pl_is_volatile(__VA_ARGS__),typeof_unqual(__VA_ARGS__),__VA_ARGS__)))),int*)restrict,pl_choose_type(pl_is_const_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const _Atomic,pl_choose_type(pl_is_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,pl_choose_type(pl_is_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,pl_choose_type(pl_is_volatile(__VA_ARGS__),typeof_unqual(__VA_ARGS__),__VA_ARGS__)))))
 #else
  #define pl_drop_volatile(/*type*/...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,pl_choose_type(pl_is_volatile(__VA_ARGS__),typeof_unqual(__VA_ARGS__),__VA_ARGS__)),int*)restrict,pl_choose_type(pl_is_const_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const _Atomic,pl_choose_type(pl_is_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,pl_choose_type(pl_is_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,pl_choose_type(pl_is_volatile(__VA_ARGS__),typeof_unqual(__VA_ARGS__),__VA_ARGS__)))))
 #endif
#else
 #define pl_drop_volatile(/*type*/...) drop_volatile_atomic(__VA_ARGS__)
#endif

// Evaluates to the argument's type without const and volatile qualifiers.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_drop_const_volatile(/*type*/...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,typeof_unqual(__VA_ARGS__)),int*)restrict,pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,typeof_unqual(__VA_ARGS__)))
 #else
  #define pl_drop_const_volatile(/*type*/...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),typeof_unqual(__VA_ARGS__),int*)restrict,pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,typeof_unqual(__VA_ARGS__)))
 #endif
#else
 #define pl_drop_const_volatile(/*type*/...) pl_drop_const_volatile_atomic(__VA_ARGS__)
#endif

// Evaluates to the argument's type without an _Atomic qualifier.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_drop_atomic(/*type*/...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_const_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const volatile,pl_choose_type(pl_is_const_atomic(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,pl_choose_type(pl_is_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,pl_choose_type(pl_is_atomic(__VA_ARGS__),typeof_unqual(__VA_ARGS__),__VA_ARGS__)))),int*)restrict,pl_choose_type(pl_is_const_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const volatile,pl_choose_type(pl_is_const_atomic(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,pl_choose_type(pl_is_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,pl_choose_type(pl_is_atomic(__VA_ARGS__),typeof_unqual(__VA_ARGS__),__VA_ARGS__)))))
 #else
  #define pl_drop_atomic(/*type*/...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),typeof(__VA_ARGS__),int*)restrict,pl_choose_type(pl_is_const_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const volatile,pl_choose_type(pl_is_const_atomic(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,pl_choose_type(pl_is_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,pl_choose_type(pl_is_atomic(__VA_ARGS__),typeof_unqual(__VA_ARGS__),__VA_ARGS__)))))
 #endif
#else
 #define pl_drop_atomic(/*type*/...) typeof(__VA_ARGS__)
#endif

// Evaluates to the argument's type without const and _Atomic qualifiers.
#define pl_drop_const_atomic(/*type*/...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,typeof_unqual(__VA_ARGS__)),int*)restrict,pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,typeof_unqual(__VA_ARGS__)))

// Evaluates to the argument's type without volatile and _Atomic qualifiers.
#define pl_drop_volatile_atomic(/*type*/...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,typeof_unqual(__VA_ARGS__)),int*)restrict,pl_choose_type(pl_is_const(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,typeof_unqual(__VA_ARGS__)))

// Evaluates to the argument's type without const, volatile, and _Atomic qualifiers.
#define pl_drop_const_volatile_atomic(/*type*/...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),typeof_unqual(__VA_ARGS__),int*)restrict,typeof_unqual(__VA_ARGS__))

// Evaluates to the argument's type without a restrict qualifier.
#ifndef __STDC_NO_ATOMICS__
 #define pl_drop_restrict(/*type*/...) pl_choose_type(pl_is_const_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const volatile _Atomic,pl_choose_type(pl_is_const_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const _Atomic,pl_choose_type(pl_is_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile _Atomic,pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,pl_choose_type(pl_is_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const volatile,pl_choose_type(pl_is_const(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,typeof_unqual(__VA_ARGS__))))))))
#else
 #define pl_drop_restrict(/*type*/...) pl_drop_atomic_restrict(__VA_ARGS__)
#endif

// Evaluates to the argument's type without const and restrict qualifiers.
#ifndef __STDC_NO_ATOMICS__
 #define pl_drop_const_restrict(/*type*/...) pl_choose_type(pl_is_volatile_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile _Atomic,pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,typeof_unqual(__VA_ARGS__))))
#else
 #define pl_drop_const_restrict(/*type*/...) pl_drop_const_atomic_restrict(__VA_ARGS__)
#endif

// Evaluates to the argument's type without volatile and restrict qualifiers.
#ifndef __STDC_NO_ATOMICS__
 #define pl_drop_volatile_restrict(/*type*/...) pl_choose_type(pl_is_const_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const _Atomic,pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,pl_choose_type(pl_is_const(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,typeof_unqual(__VA_ARGS__))))
#else
 #define pl_drop_volatile_restrict(/*type*/...) pl_drop_volatile_atomic_restrict(__VA_ARGS__)
#endif

// Evaluates to the argument's type without const, volatile, and restrict qualifiers.
#ifndef __STDC_NO_ATOMICS__
 #define pl_drop_const_volatile_restrict(/*type*/...) pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_function_or_array(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))_Atomic,typeof_unqual(__VA_ARGS__))
#else
 #define pl_drop_const_volatile_restrict(/*type*/...) typeof_unqual(__VA_ARGS__)
#endif

// Evaluates to the argument's type without _Atomic and restrict qualifiers.
#define pl_drop_atomic_restrict(/*type*/...) pl_choose_type(pl_is_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const volatile,pl_choose_type(pl_is_const(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,typeof_unqual(__VA_ARGS__))))

// Evaluates to the argument's type without const, _Atomic, and restrict qualifiers.
#define pl_drop_const_atomic_restrict(/*type*/...) pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))volatile,typeof_unqual(__VA_ARGS__))

// Evaluates to the argument's type without volatile, _Atomic, and restrict qualifiers.
#define pl_drop_volatile_atomic_restrict(/*type*/...) pl_choose_type(pl_is_const(__VA_ARGS__),pl_choose_type(pl_is_function(__VA_ARGS__),0,typeof_unqual(__VA_ARGS__))const,typeof_unqual(__VA_ARGS__))

// Evaluates to the argument's type without const, volatile, _Atomic, and restrict qualifiers.
#define pl_drop_const_volatile_atomic_restrict(/*type*/...) typeof_unqual(__VA_ARGS__)

// Evaluates to whether an identifier represents a type.
#define pl_is_type(name) _Generic(int(int(name)),int(int):0,default:1)

#endif
