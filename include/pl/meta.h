#ifndef PL_META_H
#define PL_META_H

#ifndef __GNUC__
 #warning compiler does not provide pointer type detection
#endif

#if !defined(__STDC_NO_ATOMICS__) && defined(__clang__)
 #warning compiler does not support restrict-qualified atomic pointer types
#endif

// Evaluates to whether the arguments' types are compatible.
#define pl_is_same(x, ...) _Generic((typeof(x)*)0,typeof(__VA_ARGS__)*:1,default:0)

// Evaluates to whether the arguments' types are compatible, ignoring qualifiers.
#define pl_is_same_unqual(x, ...) _Generic((typeof_unqual(x)*)0,typeof_unqual(__VA_ARGS__)*:1,default:0)

// Accepts a condition expression and two other expressions.
// The condition must be constant and integer-like.
// If the condition is truthy, evaluates to the second expression.
// Otherwise, evaluates to the third expression.
#define pl_choose(cond, x, ...) _Generic(int[1+!(cond)],int[1]:(x),default:(__VA_ARGS__))

// Accepts a condition expression and two other types or expressions.
// The condition must be constant and integer-like.
// If the condition is truthy, evaluates to the second argument's type.
// Otherwise, evaluates to the third argument's type.
#define pl_choose_type(cond, x, ...) typeof(pl_choose((cond),pl_fake(x),pl_fake(__VA_ARGS__)))

// Evaluates to an lvalue expression of the argument's type.
// Must not be used in evaluated contexts.
#define pl_fake(...) (*(typeof(__VA_ARGS__)*)0)

// Evaluates to an lvalue expression of the argument's type, ignoring qualifiers.
// Must not be used in evaluated contexts.
#define pl_fake_unqual(...) (*(typeof_unqual(__VA_ARGS__)*)0)

#ifdef __GNUC__
 // Evaluates to whether the argument's type is a pointer type.
 #define pl_is_pointer(...) (!pl_is_array(__VA_ARGS__)&&!pl_is_function(__VA_ARGS__)&&__builtin_classify_type(pl_fake(__VA_ARGS__))==5)
#endif

// Evaluates to whether the argument's type is a function type.
// Function pointer types are not considered to be function types.
#if defined(__GNUC__) && !defined(__clang__)
 #define pl_is_function(...) (__builtin_classify_type(typeof(__VA_ARGS__))==10)
#else
 #define pl_is_function(...) _Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:1,default:0)
#endif

// Evaluates to whether the argument's type is an array type.
#if defined(__GNUC__) && !defined(__clang__)
 #define pl_is_array(...) (__builtin_classify_type(typeof(__VA_ARGS__))==14)
#else
 #define pl_is_array(...) _Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:!pl_is_decayed(__VA_ARGS__))
#endif

// Evaluates to whether the argument's type is a bounded array type.
#define pl_is_bounded_array(...) _Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):0,default:!pl_is_unbounded_array(__VA_ARGS__)))

// Evaluates to whether the argument's type is an unbounded array type.
#define pl_is_unbounded_array(...) _Generic(typeof(__VA_ARGS__),typeof(*_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):(int*)0,default:_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:(int*)0,default:pl_fake(__VA_ARGS__))))[1]:_Generic(typeof(__VA_ARGS__),typeof(*_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):(int*)0,default:_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:(int*)0,default:pl_fake(__VA_ARGS__))))[2]:1,default:0),default:0)

// If the argument's type is a bounded array type, evaluates to the array's size.
// Otherwise, evaluates to zero.
#define pl_array_extent(...) (sizeof(pl_choose(pl_is_bounded_array(__VA_ARGS__),pl_fake(__VA_ARGS__),0))/sizeof(*pl_fake(pl_choose_type(pl_is_bounded_array(__VA_ARGS__),typeof(__VA_ARGS__),int(*)[2]))))

#ifdef __GNUC__
 // If the argument's type is a pointer type, evaluates to the pointee type.
 // Otherwise, evaluates to the original type.
 #define pl_drop_pointer(...) pl_choose_type(pl_is_pointer(__VA_ARGS__),*pl_fake(pl_choose_type(pl_is_pointer(__VA_ARGS__),typeof(__VA_ARGS__),int*)),__VA_ARGS__)
#endif

// If the argument's type is an array type, evaluates to the array's value type.
// Otherwise, evaluates to the original type.
#define pl_drop_extent(...) pl_choose_type(pl_is_array(__VA_ARGS__),*pl_fake(pl_choose_type(pl_is_array(__VA_ARGS__),typeof(__VA_ARGS__),int*)),__VA_ARGS__)

// Evaluates to the argument's type, decayed.
// Integer-like types are not promoted.
#define pl_decay(...) typeof(_Generic(typeof_unqual(__VA_ARGS__),unsigned char:pl_fake(__VA_ARGS__),unsigned short:pl_fake(__VA_ARGS__),signed char:pl_fake(__VA_ARGS__),short:pl_fake(__VA_ARGS__),char:pl_fake(__VA_ARGS__),bool:pl_fake(__VA_ARGS__),default:0?pl_fake(__VA_ARGS__):pl_fake(__VA_ARGS__)))

// Evaluates to whether the argument's type is decayed (i.e. cannot decay further).
#define pl_is_decayed(...) _Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):1,default:0)

// Evaluates to whether the argument's type is a void type.
#define pl_is_void(...) _Generic(typeof_unqual(__VA_ARGS__),void:1,default:0)

// Evaluates to whether the argument's type is an integer type.
#ifdef __GNUC__
 #define pl_is_int(...) (__builtin_classify_type(pl_fake(__VA_ARGS__))==1)
#else
 #define pl_is_int(...) (pl_is_unsigned(__VA_ARGS__)||pl_is_signed(__VA_ARGS__))
#endif

// Evaluates to whether the argument's type is an unsigned integer type.
#ifdef __GNUC__
 #define pl_is_unsigned(...) (__builtin_choose_expr(pl_is_int(__VA_ARGS__),(typeof(__VA_ARGS__))-1>0,0))
#else
 #define pl_is_unsigned(...) _Generic(typeof_unqual(__VA_ARGS__),unsigned char:1,unsigned short:1,unsigned int:1,unsigned long:1,unsigned long long:1,char:(char)-1<0,default:0)
#endif

// Evaluates to whether the argument's type is a signed integer type.
#ifdef __GNUC__
 #define pl_is_signed(...) (__builtin_choose_expr(pl_is_int(__VA_ARGS__),(typeof(__VA_ARGS__))-1<0,0))
#else
 #define pl_is_signed(...) _Generic(typeof_unqual(__VA_ARGS__),signed char:1,short:1,int:1,long:1,long long:1,char:(char)-1<0,default:0)
#endif

// Evaluates to whether the argument's type is a floating-point type.
#ifdef __GNUC__
 #define pl_is_float(...) (!pl_is_decimal(__VA_ARGS__)&&__builtin_classify_type(pl_fake(__VA_ARGS__))==8)
#else
 #define pl_is_float(...) _Generic(typeof_unqual(__VA_ARGS__),float:1,double:1,long double:1,default:0)
#endif

// Evaluates to whether the argument's type is a decimal floating-point type.
#ifdef __STDC_IEC_60559_DFP__
 #define pl_is_decimal(...) _Generic(typeof_unqual(__VA_ARGS__),_Decimal32:1,_Decimal64:1,_Decimal128:1,default:0)
#else
 #define pl_is_decimal(...) 0
#endif

// Evaluates to whether the argument's type has a const qualifier.
#define pl_is_const(...) _Generic(typeof(__VA_ARGS__),typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:pl_fake(__VA_ARGS__)))const:1,default:0)

// Evaluates to whether the argument's type has a volatile qualifier.
#define pl_is_volatile(...) _Generic(typeof(__VA_ARGS__),typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:pl_fake(__VA_ARGS__)))volatile:1,default:0)

// Evaluates to whether the argument's type has const and volatile qualifiers.
#define pl_is_const_volatile(...) _Generic(typeof(__VA_ARGS__),typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:pl_fake(__VA_ARGS__)))const volatile:1,default:0)

// Evaluates to whether the argument's type has an _Atomic qualifier.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_is_atomic(...) _Generic(typeof(__VA_ARGS__),typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):pl_fake(__VA_ARGS__),default:0)))_Atomic:1,default:0)
 #else
  #define pl_is_atomic(...) _Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile _Atomic:1,default:0)
 #endif
#else
 #define pl_is_atomic(...) 0
#endif

// Evaluates to whether the argument's type has const and _Atomic qualifiers.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_is_const_atomic(...) _Generic(typeof(__VA_ARGS__),typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):pl_fake(__VA_ARGS__),default:0)))const _Atomic:1,default:0)
 #else
  #define pl_is_const_atomic(...) _Generic(pl_add_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile _Atomic:1,default:0)
 #endif
#else
 #define pl_is_const_atomic(...) 0
#endif

// Evaluates to whether the argument's type has volatile and _Atomic qualifiers.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_is_volatile_atomic(...) _Generic(typeof(__VA_ARGS__),typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):pl_fake(__VA_ARGS__),default:0)))volatile _Atomic:1,default:0)
 #else
  #define pl_is_volatile_atomic(...) _Generic(pl_add_const(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile _Atomic:1,default:0)
 #endif
#else
 #define pl_is_volatile_atomic(...) 0
#endif

// Evaluates to whether the argument's type has const, volatile, and _Atomic qualifiers.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_is_const_volatile_atomic(...) _Generic(typeof(__VA_ARGS__),typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):pl_fake(__VA_ARGS__),default:0)))const volatile _Atomic:1,default:0)
 #else
  #define pl_is_const_volatile_atomic(...) _Generic(typeof(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile _Atomic:1,default:0)
 #endif
#else
 #define pl_is_const_volatile_atomic(...) 0
#endif

// Evaluates to whether the argument's type has a restrict qualifier.
#define pl_is_restrict(...) _Generic(typeof(__VA_ARGS__),pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_volatile_atomic(typeof_unqual(__VA_ARGS__)),pl_add_volatile_atomic(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_atomic(typeof_unqual(__VA_ARGS__)),pl_add_atomic(typeof_unqual(__VA_ARGS__)))),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_volatile(typeof_unqual(__VA_ARGS__)),pl_add_volatile(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)))):0,default:1)

// Evaluates to whether the argument's type has const and restrict qualifiers.
#define pl_is_const_restrict(...) (pl_is_const(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))

// Evaluates to whether the argument's type has volatile and restrict qualifiers.
#define pl_is_volatile_restrict(...) (pl_is_volatile(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))

// Evaluates to whether the argument's type has const, volatile, and restrict qualifiers.
#define pl_is_const_volatile_restrict(...) (pl_is_const_volatile(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))

// Evaluates to whether the argument's type has _Atomic and restrict qualifiers.
#if !defined(__STDC_NO_ATOMICS__) && !defined(__clang__)
 #define pl_is_atomic_restrict(...) (pl_is_atomic(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))
#else
 #define pl_is_atomic_restrict(...) 0
#endif

// Evaluates to whether the argument's type has const, _Atomic, and restrict qualifiers.
#if !defined(__STDC_NO_ATOMICS__) && !defined(__clang__)
 #define pl_is_const_atomic_restrict(...) (pl_is_const_atomic(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))
#else
 #define pl_is_const_atomic_restrict(...) 0
#endif

// Evaluates to whether the argument's type has volatile, _Atomic, and restrict qualifiers.
#if !defined(__STDC_NO_ATOMICS__) && !defined(__clang__)
 #define pl_is_volatile_atomic_restrict(...) (pl_is_volatile_atomic(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))
#else
 #define pl_is_volatile_atomic_restrict(...) 0
#endif

// Evaluates to whether the argument's type has const, volatile, _Atomic, and restrict qualifiers.
#if !defined(__STDC_NO_ATOMICS__) && !defined(__clang__)
 #define pl_is_const_volatile_atomic_restrict(...) (pl_is_const_volatile_atomic(__VA_ARGS__)&&pl_is_restrict(__VA_ARGS__))
#else
 #define pl_is_const_volatile_atomic_restrict(...) 0
#endif

// Evaluates to the argument's type with a const qualifier.
// If the argument's type is a function type, it is unchanged.
#define pl_add_const(...) typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:pl_fake(__VA_ARGS__),default:pl_fake(typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:pl_fake(__VA_ARGS__)))const)))

// Evaluates to the argument's type with a volatile qualifier.
// If the argument's type is a function type, it is unchanged.
#define pl_add_volatile(...) typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:pl_fake(__VA_ARGS__),default:pl_fake(typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:pl_fake(__VA_ARGS__)))volatile)))

// Evaluates to the argument's type with const and volatile qualifiers.
// If the argument's type is a function type, it is unchanged.
#define pl_add_const_volatile(...) typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:pl_fake(__VA_ARGS__),default:pl_fake(typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:pl_fake(__VA_ARGS__)))const volatile)))

// Evaluates to the argument's type with an _Atomic qualifier.
// If the argument's type is a function or array type, it is unchanged.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_add_atomic(...) typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:pl_fake(__VA_ARGS__),default:_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:pl_fake(typeof(_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):pl_fake(__VA_ARGS__),default:0))_Atomic)),default:pl_fake(__VA_ARGS__))))
 #else
  // If the argument's type has a restrict qualifier, _Atomic is not applied.
  #define pl_add_atomic(...) typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(__VA_ARGS__),default:0))_Atomic),default:pl_fake(__VA_ARGS__)))
 #endif
#else
 #define pl_add_atomic(...) typeof(__VA_ARGS__)
#endif

// Evaluates to the argument's type with const and _Atomic qualifiers.
// If the argument's type is a function or array type, it is unchanged.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_add_const_atomic(...) typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:pl_fake(__VA_ARGS__),default:_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:pl_fake(typeof(_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):pl_fake(__VA_ARGS__),default:0))const _Atomic)),default:pl_fake(__VA_ARGS__))))
 #else
  // If the argument's type is void or has a restrict qualifier, _Atomic is not applied.
  #define pl_add_const_atomic(...) typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(__VA_ARGS__),default:0))const _Atomic),default:pl_fake(pl_add_const(__VA_ARGS__))))
 #endif
#else
 #define pl_add_const_atomic(...) pl_add_const(__VA_ARGS__)
#endif

// Evaluates to the argument's type with volatile and _Atomic qualifiers.
// If the argument's type is a function or array type, it is unchanged.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_add_volatile_atomic(...) typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:pl_fake(__VA_ARGS__),default:_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:pl_fake(typeof(_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):pl_fake(__VA_ARGS__),default:0))volatile _Atomic)),default:pl_fake(__VA_ARGS__))))
 #else
  // If the argument's type is void or has a restrict qualifier, _Atomic is not applied.
  #define pl_add_volatile_atomic(...) typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(__VA_ARGS__),default:0))volatile _Atomic),default:pl_fake(pl_add_volatile(__VA_ARGS__))))
 #endif
#else
 #define pl_add_volatile_atomic(...) pl_add_volatile(__VA_ARGS__)
#endif

// Evaluates to the argument's type with const, volatile, and _Atomic qualifiers.
// If the argument's type is a function or array type, it is unchanged.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_add_const_volatile_atomic(...) typeof(_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:pl_fake(__VA_ARGS__),default:_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):_Generic(pl_fake(__VA_ARGS__),typeof(__VA_ARGS__)*:0,default:pl_fake(typeof(_Generic(typeof_unqual(__VA_ARGS__),typeof_unqual(pl_decay(__VA_ARGS__)):pl_fake(__VA_ARGS__),default:0))const volatile _Atomic)),default:pl_fake(__VA_ARGS__))))
 #else
  // If the argument's type is void or has a restrict qualifier, _Atomic is not applied.
  #define pl_add_const_volatile_atomic(...) typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(typeof(_Generic(pl_add_const_volatile(__VA_ARGS__),pl_choose_type(pl_is_decayed(__VA_ARGS__)&&!pl_is_void(__VA_ARGS__),typeof_unqual(__VA_ARGS__),0)const volatile:pl_fake(__VA_ARGS__),default:0))const volatile _Atomic),default:pl_fake(pl_add_const_volatile(__VA_ARGS__))))
 #endif
#else
 #define pl_add_const_volatile_atomic(...) pl_add_const_volatile(__VA_ARGS__)
#endif

#ifdef __GNUC__
 // Evaluates to the argument's type with a restrict qualifier.
 // If the argument's type is not a pointer, restrict is not applied.
 #define pl_add_restrict(...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),typeof(__VA_ARGS__),int*)restrict,__VA_ARGS__)
#endif

#ifdef __GNUC__
 // Evaluates to the argument's type with const and restrict qualifiers.
 // If the argument's type is a function or array type, const is not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #define pl_add_const_restrict(...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_const(__VA_ARGS__),int*)restrict,pl_add_const(__VA_ARGS__))
#endif

#ifdef __GNUC__
 // Evaluates to the argument's type with volatile and restrict qualifiers.
 // If the argument's type is a function or array type, volatile is not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #define pl_add_volatile_restrict(...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_volatile(__VA_ARGS__),int*)restrict,pl_add_volatile(__VA_ARGS__))
#endif

#ifdef __GNUC__
 // Evaluates to the argument's type with const, volatile, and restrict qualifiers.
 // If the argument's type is a function or array type, const and volatile are not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #define pl_add_const_volatile_restrict(...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_const_volatile(__VA_ARGS__),int*)restrict,pl_add_const_volatile(__VA_ARGS__))
#endif

#if defined(__GNUC__) && !defined(__clang__)
 // Evaluates to the argument's type with _Atomic and restrict qualifiers.
 // If the argument's type is a function or array type, _Atomic is not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #ifndef __STDC_NO_ATOMICS__
  #define pl_add_atomic_restrict(...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_atomic(__VA_ARGS__),int*)restrict,pl_add_atomic(__VA_ARGS__))
 #else
  #define pl_add_atomic_restrict(...) pl_add_restrict(__VA_ARGS__)
 #endif
#endif

#if defined(__GNUC__) && !defined(__clang__)
 // Evaluates to the argument's type with const, _Atomic, and restrict qualifiers.
 // If the argument's type is a function or array type, const and _Atomic are not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #ifndef __STDC_NO_ATOMICS__
  #define pl_add_const_atomic_restrict(...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_const_atomic(__VA_ARGS__),int*)restrict,pl_add_const_atomic(__VA_ARGS__))
 #else
  #define pl_add_const_atomic_restrict(...) pl_add_const_restrict(__VA_ARGS__)
 #endif
#endif

#if defined(__GNUC__) && !defined(__clang__)
 // Evaluates to the argument's type with volatile, _Atomic, and restrict qualifiers.
 // If the argument's type is a function or array type, volatile and _Atomic are not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #ifndef __STDC_NO_ATOMICS__
  #define pl_add_volatile_atomic_restrict(...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_volatile_atomic(__VA_ARGS__),int*)restrict,pl_add_volatile_atomic(__VA_ARGS__))
 #else
  #define pl_add_volatile_atomic_restrict(...) pl_add_volatile_restrict(__VA_ARGS__)
 #endif
#endif

#if defined(__GNUC__) && !defined(__clang__)
 // Evaluates to the argument's type with const, volatile, _Atomic, and restrict qualifiers.
 // If the argument's type is a function or array type, const and _Atomic are not applied.
 // If the argument's type is not a pointer, restrict is not applied.
 #ifndef __STDC_NO_ATOMICS__
  #define pl_add_const_volatile_atomic_restrict(...) pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_choose_type(pl_is_pointer(__VA_ARGS__),pl_add_const_volatile_atomic(__VA_ARGS__),int*)restrict,pl_add_const_volatile_atomic(__VA_ARGS__))
 #else
  #define pl_add_const_volatile_atomic_restrict(...) pl_add_const_volatile_restrict(__VA_ARGS__)
 #endif
#endif

// Evaluates to the argument's type without a const qualifier.
#ifndef __clang__
 #define pl_drop_const(...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile_atomic(typeof_unqual(__VA_ARGS__)),pl_add_atomic(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))),int*)restrict,pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile_atomic(typeof_unqual(__VA_ARGS__)),pl_add_atomic(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))))
#else
 #define pl_drop_const(...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)),int*)restrict,pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile_atomic(typeof_unqual(__VA_ARGS__)),pl_add_atomic(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))))
#endif

// Evaluates to the argument's type without a volatile qualifier.
#ifndef __clang__
 #define pl_drop_volatile(...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_atomic(typeof_unqual(__VA_ARGS__)),pl_add_atomic(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))),int*)restrict,pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_atomic(typeof_unqual(__VA_ARGS__)),pl_add_atomic(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))))
#else
 #define pl_drop_volatile(...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)),int*)restrict,pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_atomic(typeof_unqual(__VA_ARGS__)),pl_add_atomic(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))))
#endif

// Evaluates to the argument's type without const and volatile qualifiers.
#ifndef __clang__
 #define pl_drop_const_volatile(...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_add_atomic(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)),int*)restrict,pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_add_atomic(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)))
#else
 #define pl_drop_const_volatile(...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),typeof_unqual(__VA_ARGS__),int*)restrict,pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_add_atomic(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)))
#endif

// Evaluates to the argument's type without an _Atomic qualifier.
#ifndef __STDC_NO_ATOMICS__
 #ifndef __clang__
  #define pl_drop_atomic(...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_volatile(typeof_unqual(__VA_ARGS__)),pl_add_volatile(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))),int*)restrict,pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_volatile(typeof_unqual(__VA_ARGS__)),pl_add_volatile(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))))
 #else
  #define pl_drop_atomic(...) pl_choose_type(pl_is_restrict(__VA_ARGS__),typeof(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_volatile(typeof_unqual(__VA_ARGS__)),pl_add_volatile(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))))
 #endif
#else
 #define pl_drop_atomic(...) typeof(__VA_ARGS__)
#endif

// Evaluates to the argument's type without const and _Atomic qualifiers.
#define pl_drop_const_atomic(...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)),int*)restrict,pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)))

// Evaluates to the argument's type without volatile and _Atomic qualifiers.
#define pl_drop_volatile_atomic(...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)),int*)restrict,pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)))

// Evaluates to the argument's type without const, volatile, and _Atomic qualifiers.
#define pl_drop_const_volatile_atomic(...) pl_choose_type(pl_is_restrict(__VA_ARGS__),pl_choose_type(pl_is_restrict(__VA_ARGS__),typeof_unqual(__VA_ARGS__),int*)restrict,typeof_unqual(__VA_ARGS__))

// Evaluates to the argument's type without a restrict qualifier.
#ifndef __clang__
 #define pl_drop_restrict(...) pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_volatile_atomic(typeof_unqual(__VA_ARGS__)),pl_add_volatile_atomic(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_atomic(typeof_unqual(__VA_ARGS__)),pl_add_atomic(typeof_unqual(__VA_ARGS__)))),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_volatile(typeof_unqual(__VA_ARGS__)),pl_add_volatile(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))))
#else
 #define pl_drop_restrict(...) pl_choose_type(pl_is_atomic(__VA_ARGS__),typeof(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_volatile(typeof_unqual(__VA_ARGS__)),pl_add_volatile(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))))
#endif

// Evaluates to the argument's type without const and restrict qualifiers.
#define pl_drop_const_restrict(...) pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile_atomic(typeof_unqual(__VA_ARGS__)),pl_add_atomic(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)))

// Evaluates to the argument's type without volatile and restrict qualifiers.
#define pl_drop_volatile_restrict(...) pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_atomic(typeof_unqual(__VA_ARGS__)),pl_add_atomic(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)))

// Evaluates to the argument's type without const, volatile, and restrict qualifiers.
#define pl_drop_const_volatile_restrict(...) pl_choose_type(pl_is_atomic(__VA_ARGS__),pl_add_atomic(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))

// Evaluates to the argument's type without _Atomic and restrict qualifiers.
#define pl_drop_atomic_restrict(...) pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const_volatile(typeof_unqual(__VA_ARGS__)),pl_add_volatile(typeof_unqual(__VA_ARGS__))),pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__)))

// Evaluates to the argument's type without const, _Atomic, and restrict qualifiers.
#define pl_drop_const_atomic_restrict(...) pl_choose_type(pl_is_volatile(__VA_ARGS__),pl_add_volatile(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))

// Evaluates to the argument's type without volatile, _Atomic, and restrict qualifiers.
#define pl_drop_volatile_atomic_restrict(...) pl_choose_type(pl_is_const(__VA_ARGS__),pl_add_const(typeof_unqual(__VA_ARGS__)),typeof_unqual(__VA_ARGS__))

// Evaluates to the argument's type without const, volatile, _Atomic, and restrict qualifiers.
#define pl_drop_const_volatile_atomic_restrict(...) typeof_unqual(__VA_ARGS__)

// Evaluates to whether an identifier represents a type.
#define pl_is_type(name) (!pl_is_same(int(int(name)),int(int)))

#endif
