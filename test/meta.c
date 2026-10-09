#include <pl/meta.h>

int main() {}
struct incomplete;

static_assert(pl_is_same(int, int));
static_assert(!pl_is_same(int, char));
static_assert(!pl_is_same(int, int const));
static_assert(!pl_is_same(int, int*));
static_assert(pl_is_same(int*, int*));
static_assert(!pl_is_same(int*, int const*));
static_assert(!pl_is_same(int*, int* const));
static_assert(pl_is_same(int(), int()));
static_assert(pl_is_same(int(int), int(int)));
static_assert(pl_is_same(int(int), int(int const)));
static_assert(!pl_is_same(int(int), int(char)));
static_assert(!pl_is_same(int(int), int));
static_assert(!pl_is_same(int(int), int(*)(int)));
static_assert(pl_is_same(int[], int[]));
static_assert(!pl_is_same(int[], int));
static_assert(pl_is_same(int[1], int[1]));
static_assert(!pl_is_same(int[1], int));
static_assert(!pl_is_same(int[1], int*));
static_assert(pl_is_same(int[1], int[]));
static_assert(pl_is_same(int(*)[1], int(*)[]));
static_assert(pl_is_same(42, int));
static_assert(pl_is_same("Hello", char[6]));

static_assert(pl_is_same_unqual(int, int const volatile _Atomic));
static_assert(pl_is_same_unqual(int[], int const[]));
static_assert(!pl_is_same_unqual(int(int*), int(int const*)));

static_assert(pl_choose(true, 1, 2) == 1);
static_assert(pl_choose(false, 1, 2) == 2);

static_assert(pl_is_same(pl_choose_type(true, int, char), int));
static_assert(pl_is_same(pl_choose_type(false, int, char), char));

static_assert(pl_is_same(typeof(pl_fake(int) + 1), int));
static_assert(pl_is_same(typeof(pl_fake(*pl_fake(int const*))), int const));

static_assert(pl_is_same(typeof(pl_fake_unqual(*pl_fake(int const*))), int));

#ifdef __GNUC__
static_assert(!pl_is_pointer(int));
static_assert(pl_is_pointer(int*));
static_assert(pl_is_pointer(int* const));
static_assert(!pl_is_pointer(int()));
static_assert(!pl_is_pointer(int[]));
static_assert(!pl_is_pointer(int[1]));
#endif

static_assert(!pl_is_function(int));
static_assert(pl_is_function(int()));
static_assert(pl_is_function(int(int)));
static_assert(pl_is_function(int(...)));
static_assert(!pl_is_function(int(*)(int)));
static_assert(!pl_is_function(struct incomplete));

static_assert(!pl_is_array(int));
static_assert(!pl_is_array(int*));
static_assert(pl_is_array(int[]));
static_assert(pl_is_array(int[1]));
static_assert(!pl_is_array(int()));
static_assert(!pl_is_array(char));
static_assert(!pl_is_array(float));
static_assert(!pl_is_array(int* const));
static_assert(!pl_is_array(struct incomplete));

static_assert(!pl_is_sized_array(int));
static_assert(pl_is_sized_array(int[1]));
static_assert(!pl_is_sized_array(int[]));
static_assert(!pl_is_sized_array(int()));

static_assert(!pl_is_unsized_array(int));
static_assert(!pl_is_unsized_array(int[1]));
static_assert(pl_is_unsized_array(int[]));
static_assert(!pl_is_unsized_array(int()));

static_assert(pl_extent(int[1]) == 1);
static_assert(pl_extent(int[2]) == 2);
static_assert(pl_extent(int[3]) == 3);
static_assert(pl_extent(int[]) == 0);
static_assert(pl_extent(int) == 0);

static_assert(pl_is_same(pl_drop_pointer(int), int));
static_assert(pl_is_same(pl_drop_pointer(int*), int));
static_assert(pl_is_same(pl_drop_pointer(int**), int*));
static_assert(pl_is_same(pl_drop_pointer(int const*), int const));
static_assert(pl_is_same(pl_drop_pointer(int* const*), int* const));
static_assert(pl_is_same(pl_drop_pointer(int(*)[]), int[]));
static_assert(pl_is_same(pl_drop_pointer(int(*)()), int()));
static_assert(pl_is_same(pl_drop_pointer(int[]), int[]));

static_assert(pl_is_same(pl_drop_extent(int), int));
static_assert(pl_is_same(pl_drop_extent(int*), int*));
static_assert(pl_is_same(pl_drop_extent(int[]), int));
static_assert(pl_is_same(pl_drop_extent(int[1]), int));
static_assert(pl_is_same(pl_drop_extent("Hello"), char));
static_assert(pl_is_same(pl_drop_extent(int const volatile[]), int const volatile));

static_assert(pl_is_decayed(int));
static_assert(pl_is_decayed(int*));
static_assert(pl_is_decayed(int(*)(int)));
static_assert(!pl_is_decayed(int[]));
static_assert(!pl_is_decayed(int[1]));
static_assert(!pl_is_decayed(int()));
static_assert(pl_is_decayed(char));
static_assert(pl_is_decayed(float));
static_assert(pl_is_decayed(int* const));
static_assert(pl_is_decayed(struct incomplete));

static_assert(pl_is_same(pl_decay(int), int));
static_assert(pl_is_same(pl_decay(char), char));
static_assert(pl_is_same(pl_decay(int[]), int*));
static_assert(pl_is_same(pl_decay(int[1]), int*));
static_assert(pl_is_same(pl_decay(int()), int(*)()));
static_assert(pl_is_same(pl_decay(struct incomplete), struct incomplete));

static_assert(pl_is_int(int));
static_assert(pl_is_int(int const));
static_assert(!pl_is_int(int*));
static_assert(!pl_is_int(int[]));
static_assert(!pl_is_int(int()));
#ifdef __GNUC__
__extension__ static_assert(pl_is_int(__int128));
#endif
static_assert(!pl_is_int(struct{ int _; }));

static_assert(pl_is_unsigned_int(unsigned char));
static_assert(pl_is_unsigned_int(unsigned short));
static_assert(pl_is_unsigned_int(unsigned int));
static_assert(pl_is_unsigned_int(unsigned long));
static_assert(pl_is_unsigned_int(unsigned long long));
static_assert(pl_is_unsigned_int(bool));
static_assert(((char)-1 < 0) || pl_is_unsigned_int(char));
static_assert(!pl_is_unsigned_int(short));
static_assert(!pl_is_unsigned_int(int));
static_assert(!pl_is_unsigned_int(long));
static_assert(!pl_is_unsigned_int(long long));
static_assert(!pl_is_unsigned_int(struct{ int _; }));

static_assert(pl_is_signed_int(signed char));
static_assert(pl_is_signed_int(short));
static_assert(pl_is_signed_int(int));
static_assert(pl_is_signed_int(long));
static_assert(pl_is_signed_int(long long));
static_assert(((char)-1 > 0) || pl_is_signed_int(char));
static_assert(!pl_is_signed_int(unsigned char));
static_assert(!pl_is_signed_int(unsigned short));
static_assert(!pl_is_signed_int(unsigned int));
static_assert(!pl_is_signed_int(unsigned long));
static_assert(!pl_is_signed_int(unsigned long long));
static_assert(!pl_is_signed_int(bool));
static_assert(!pl_is_signed_int(struct{ int _; }));

static_assert(pl_is_same(pl_make_unsigned_int(int), unsigned int));
static_assert(pl_is_same(pl_make_unsigned_int(unsigned int), unsigned int));
static_assert(pl_is_same(pl_make_unsigned_int(float), float));
#if defined(__GNUC__) && !defined(__clang__)
static_assert(pl_is_same(pl_make_unsigned_int(_BitInt(42)), unsigned _BitInt(42)));
#endif

static_assert(pl_is_same(pl_make_signed_int(unsigned int), int));
static_assert(pl_is_same(pl_make_signed_int(int), int));
static_assert(pl_is_same(pl_make_signed_int(float), float));
#if defined(__GNUC__) && !defined(__clang__)
static_assert(pl_is_same(pl_make_signed_int(unsigned _BitInt(42)), _BitInt(42)));
#endif

static_assert(pl_int_width(char) == pl_int_width(unsigned char));
static_assert(pl_int_width(short) == pl_int_width(unsigned short));
static_assert(pl_int_width(int) == pl_int_width(unsigned int));
static_assert(pl_int_width(long) == pl_int_width(unsigned long));
static_assert(pl_int_width(long long) == pl_int_width(unsigned long long));
static_assert(pl_int_width(bool) == 1);
static_assert(pl_int_width(float) == 0);
#if defined(__GNUC__) && !defined(__clang__)
static_assert(pl_int_width(_BitInt(42)) == 42);
#endif
static_assert(pl_int_width(struct{ int _; }) == 0);

static_assert(!pl_is_float(int));
static_assert(pl_is_float(float));
static_assert(pl_is_float(double));
static_assert(pl_is_float(long double));
#ifdef __GNUC__
static_assert(pl_is_float(__float128));
#endif
#ifdef __STDC_IEC_60559_DFP__
static_assert(!pl_is_float(_Decimal32));
#endif
static_assert(!pl_is_float(union { int _; }));

#ifdef __STDC_IEC_60559_DFP__
static_assert(!pl_is_decimal(int));
static_assert(!pl_is_decimal(float));
static_assert(pl_is_decimal(_Decimal32));
static_assert(pl_is_decimal(_Decimal64));
static_assert(pl_is_decimal(_Decimal128));
#endif

static_assert(!pl_is_const(int));
static_assert(pl_is_const(int const));
static_assert(!pl_is_const(int volatile));
static_assert(pl_is_const(int const volatile));
static_assert(!pl_is_const(int _Atomic));
static_assert(pl_is_const(int const _Atomic));
static_assert(!pl_is_const(int volatile _Atomic));
static_assert(pl_is_const(int const volatile _Atomic));
static_assert(!pl_is_const(int* restrict));
static_assert(pl_is_const(int* const restrict));
static_assert(!pl_is_const(int* volatile restrict));
static_assert(pl_is_const(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_const(int* _Atomic restrict));
static_assert(pl_is_const(int* const _Atomic restrict));
static_assert(!pl_is_const(int* volatile _Atomic restrict));
static_assert(pl_is_const(int* const volatile _Atomic restrict));
#endif
static_assert(!pl_is_const(int()));
static_assert(pl_is_const(struct incomplete const));

static_assert(!pl_is_volatile(int));
static_assert(!pl_is_volatile(int const));
static_assert(pl_is_volatile(int volatile));
static_assert(pl_is_volatile(int const volatile));
static_assert(!pl_is_volatile(int _Atomic));
static_assert(!pl_is_volatile(int const _Atomic));
static_assert(pl_is_volatile(int volatile _Atomic));
static_assert(pl_is_volatile(int const volatile _Atomic));
static_assert(!pl_is_volatile(int* restrict));
static_assert(!pl_is_volatile(int* const restrict));
static_assert(pl_is_volatile(int* volatile restrict));
static_assert(pl_is_volatile(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_volatile(int* _Atomic restrict));
static_assert(!pl_is_volatile(int* const _Atomic restrict));
static_assert(pl_is_volatile(int* volatile _Atomic restrict));
static_assert(pl_is_volatile(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_const_volatile(int));
static_assert(!pl_is_const_volatile(int const));
static_assert(!pl_is_const_volatile(int volatile));
static_assert(pl_is_const_volatile(int const volatile));
static_assert(!pl_is_const_volatile(int _Atomic));
static_assert(!pl_is_const_volatile(int const _Atomic));
static_assert(!pl_is_const_volatile(int volatile _Atomic));
static_assert(pl_is_const_volatile(int const volatile _Atomic));
static_assert(!pl_is_const_volatile(int* restrict));
static_assert(!pl_is_const_volatile(int* const restrict));
static_assert(!pl_is_const_volatile(int* volatile restrict));
static_assert(pl_is_const_volatile(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_const_volatile(int* _Atomic restrict));
static_assert(!pl_is_const_volatile(int* const _Atomic restrict));
static_assert(!pl_is_const_volatile(int* volatile _Atomic restrict));
static_assert(pl_is_const_volatile(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_atomic(int));
static_assert(!pl_is_atomic(int const));
static_assert(!pl_is_atomic(int volatile));
static_assert(!pl_is_atomic(int const volatile));
static_assert(pl_is_atomic(int _Atomic));
static_assert(pl_is_atomic(int const _Atomic));
static_assert(pl_is_atomic(int volatile _Atomic));
static_assert(pl_is_atomic(int const volatile _Atomic));
static_assert(!pl_is_atomic(int* restrict));
static_assert(!pl_is_atomic(int* const restrict));
static_assert(!pl_is_atomic(int* volatile restrict));
static_assert(!pl_is_atomic(int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_atomic(int* _Atomic restrict));
static_assert(pl_is_atomic(int* const _Atomic restrict));
static_assert(pl_is_atomic(int* volatile _Atomic restrict));
static_assert(pl_is_atomic(int* const volatile _Atomic restrict));
#endif
static_assert(!pl_is_atomic(int[]));
static_assert(!pl_is_atomic(int()));
static_assert(!pl_is_atomic(void));

static_assert(!pl_is_const_atomic(int));
static_assert(!pl_is_const_atomic(int const));
static_assert(!pl_is_const_atomic(int volatile));
static_assert(!pl_is_const_atomic(int const volatile));
static_assert(!pl_is_const_atomic(int _Atomic));
static_assert(pl_is_const_atomic(int const _Atomic));
static_assert(!pl_is_const_atomic(int volatile _Atomic));
static_assert(pl_is_const_atomic(int const volatile _Atomic));
static_assert(!pl_is_const_atomic(int* restrict));
static_assert(!pl_is_const_atomic(int* const restrict));
static_assert(!pl_is_const_atomic(int* volatile restrict));
static_assert(!pl_is_const_atomic(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_const_atomic(int* _Atomic restrict));
static_assert(pl_is_const_atomic(int* const _Atomic restrict));
static_assert(!pl_is_const_atomic(int* volatile _Atomic restrict));
static_assert(pl_is_const_atomic(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_volatile_atomic(int));
static_assert(!pl_is_volatile_atomic(int const));
static_assert(!pl_is_volatile_atomic(int volatile));
static_assert(!pl_is_volatile_atomic(int const volatile));
static_assert(!pl_is_volatile_atomic(int _Atomic));
static_assert(!pl_is_volatile_atomic(int const _Atomic));
static_assert(pl_is_volatile_atomic(int volatile _Atomic));
static_assert(pl_is_volatile_atomic(int const volatile _Atomic));
static_assert(!pl_is_volatile_atomic(int* restrict));
static_assert(!pl_is_volatile_atomic(int* const restrict));
static_assert(!pl_is_volatile_atomic(int* volatile restrict));
static_assert(!pl_is_volatile_atomic(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_volatile_atomic(int* _Atomic restrict));
static_assert(!pl_is_volatile_atomic(int* const _Atomic restrict));
static_assert(pl_is_volatile_atomic(int* volatile _Atomic restrict));
static_assert(pl_is_volatile_atomic(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_const_volatile_atomic(int));
static_assert(!pl_is_const_volatile_atomic(int const));
static_assert(!pl_is_const_volatile_atomic(int volatile));
static_assert(!pl_is_const_volatile_atomic(int const volatile));
static_assert(!pl_is_const_volatile_atomic(int _Atomic));
static_assert(!pl_is_const_volatile_atomic(int const _Atomic));
static_assert(!pl_is_const_volatile_atomic(int volatile _Atomic));
static_assert(pl_is_const_volatile_atomic(int const volatile _Atomic));
static_assert(!pl_is_const_volatile_atomic(int* restrict));
static_assert(!pl_is_const_volatile_atomic(int* const restrict));
static_assert(!pl_is_const_volatile_atomic(int* volatile restrict));
static_assert(!pl_is_const_volatile_atomic(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_const_volatile_atomic(int* _Atomic restrict));
static_assert(!pl_is_const_volatile_atomic(int* const _Atomic restrict));
static_assert(!pl_is_const_volatile_atomic(int* volatile _Atomic restrict));
static_assert(pl_is_const_volatile_atomic(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_restrict(int));
static_assert(!pl_is_restrict(int const));
static_assert(!pl_is_restrict(int volatile));
static_assert(!pl_is_restrict(int const volatile));
static_assert(!pl_is_restrict(int _Atomic));
static_assert(!pl_is_restrict(int const _Atomic));
static_assert(!pl_is_restrict(int volatile _Atomic));
static_assert(!pl_is_restrict(int const volatile _Atomic));
static_assert(pl_is_restrict(int* restrict));
static_assert(pl_is_restrict(int* const restrict));
static_assert(pl_is_restrict(int* volatile restrict));
static_assert(pl_is_restrict(int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_restrict(int* _Atomic restrict));
static_assert(pl_is_restrict(int* const _Atomic restrict));
static_assert(pl_is_restrict(int* volatile _Atomic restrict));
static_assert(pl_is_restrict(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_const_restrict(int));
static_assert(!pl_is_const_restrict(int const));
static_assert(!pl_is_const_restrict(int volatile));
static_assert(!pl_is_const_restrict(int const volatile));
static_assert(!pl_is_const_restrict(int _Atomic));
static_assert(!pl_is_const_restrict(int const _Atomic));
static_assert(!pl_is_const_restrict(int volatile _Atomic));
static_assert(!pl_is_const_restrict(int const volatile _Atomic));
static_assert(!pl_is_const_restrict(int* restrict));
static_assert(pl_is_const_restrict(int* const restrict));
static_assert(!pl_is_const_restrict(int* volatile restrict));
static_assert(pl_is_const_restrict(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_const_restrict(int* _Atomic restrict));
static_assert(pl_is_const_restrict(int* const _Atomic restrict));
static_assert(!pl_is_const_restrict(int* volatile _Atomic restrict));
static_assert(pl_is_const_restrict(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_volatile_restrict(int));
static_assert(!pl_is_volatile_restrict(int const));
static_assert(!pl_is_volatile_restrict(int volatile));
static_assert(!pl_is_volatile_restrict(int const volatile));
static_assert(!pl_is_volatile_restrict(int _Atomic));
static_assert(!pl_is_volatile_restrict(int const _Atomic));
static_assert(!pl_is_volatile_restrict(int volatile _Atomic));
static_assert(!pl_is_volatile_restrict(int const volatile _Atomic));
static_assert(!pl_is_volatile_restrict(int* restrict));
static_assert(!pl_is_volatile_restrict(int* const restrict));
static_assert(pl_is_volatile_restrict(int* volatile restrict));
static_assert(pl_is_volatile_restrict(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_volatile_restrict(int* _Atomic restrict));
static_assert(!pl_is_volatile_restrict(int* const _Atomic restrict));
static_assert(pl_is_volatile_restrict(int* volatile _Atomic restrict));
static_assert(pl_is_volatile_restrict(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_const_volatile_restrict(int));
static_assert(!pl_is_const_volatile_restrict(int const));
static_assert(!pl_is_const_volatile_restrict(int volatile));
static_assert(!pl_is_const_volatile_restrict(int const volatile));
static_assert(!pl_is_const_volatile_restrict(int _Atomic));
static_assert(!pl_is_const_volatile_restrict(int const _Atomic));
static_assert(!pl_is_const_volatile_restrict(int volatile _Atomic));
static_assert(!pl_is_const_volatile_restrict(int const volatile _Atomic));
static_assert(!pl_is_const_volatile_restrict(int* restrict));
static_assert(!pl_is_const_volatile_restrict(int* const restrict));
static_assert(!pl_is_const_volatile_restrict(int* volatile restrict));
static_assert(pl_is_const_volatile_restrict(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_const_volatile_restrict(int* _Atomic restrict));
static_assert(!pl_is_const_volatile_restrict(int* const _Atomic restrict));
static_assert(!pl_is_const_volatile_restrict(int* volatile _Atomic restrict));
static_assert(pl_is_const_volatile_restrict(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_atomic_restrict(int));
static_assert(!pl_is_atomic_restrict(int const));
static_assert(!pl_is_atomic_restrict(int volatile));
static_assert(!pl_is_atomic_restrict(int const volatile));
static_assert(!pl_is_atomic_restrict(int _Atomic));
static_assert(!pl_is_atomic_restrict(int const _Atomic));
static_assert(!pl_is_atomic_restrict(int volatile _Atomic));
static_assert(!pl_is_atomic_restrict(int const volatile _Atomic));
static_assert(!pl_is_atomic_restrict(int* restrict));
static_assert(!pl_is_atomic_restrict(int* const restrict));
static_assert(!pl_is_atomic_restrict(int* volatile restrict));
static_assert(!pl_is_atomic_restrict(int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_atomic_restrict(int* _Atomic restrict));
static_assert(pl_is_atomic_restrict(int* const _Atomic restrict));
static_assert(pl_is_atomic_restrict(int* volatile _Atomic restrict));
static_assert(pl_is_atomic_restrict(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_const_atomic_restrict(int));
static_assert(!pl_is_const_atomic_restrict(int const));
static_assert(!pl_is_const_atomic_restrict(int volatile));
static_assert(!pl_is_const_atomic_restrict(int const volatile));
static_assert(!pl_is_const_atomic_restrict(int _Atomic));
static_assert(!pl_is_const_atomic_restrict(int const _Atomic));
static_assert(!pl_is_const_atomic_restrict(int volatile _Atomic));
static_assert(!pl_is_const_atomic_restrict(int const volatile _Atomic));
static_assert(!pl_is_const_atomic_restrict(int* restrict));
static_assert(!pl_is_const_atomic_restrict(int* const restrict));
static_assert(!pl_is_const_atomic_restrict(int* volatile restrict));
static_assert(!pl_is_const_atomic_restrict(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_const_atomic_restrict(int* _Atomic restrict));
static_assert(pl_is_const_atomic_restrict(int* const _Atomic restrict));
static_assert(!pl_is_const_atomic_restrict(int* volatile _Atomic restrict));
static_assert(pl_is_const_atomic_restrict(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_volatile_atomic_restrict(int));
static_assert(!pl_is_volatile_atomic_restrict(int const));
static_assert(!pl_is_volatile_atomic_restrict(int volatile));
static_assert(!pl_is_volatile_atomic_restrict(int const volatile));
static_assert(!pl_is_volatile_atomic_restrict(int _Atomic));
static_assert(!pl_is_volatile_atomic_restrict(int const _Atomic));
static_assert(!pl_is_volatile_atomic_restrict(int volatile _Atomic));
static_assert(!pl_is_volatile_atomic_restrict(int const volatile _Atomic));
static_assert(!pl_is_volatile_atomic_restrict(int* restrict));
static_assert(!pl_is_volatile_atomic_restrict(int* const restrict));
static_assert(!pl_is_volatile_atomic_restrict(int* volatile restrict));
static_assert(!pl_is_volatile_atomic_restrict(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_volatile_atomic_restrict(int* _Atomic restrict));
static_assert(!pl_is_volatile_atomic_restrict(int* const _Atomic restrict));
static_assert(pl_is_volatile_atomic_restrict(int* volatile _Atomic restrict));
static_assert(pl_is_volatile_atomic_restrict(int* const volatile _Atomic restrict));
#endif

static_assert(!pl_is_const_volatile_atomic_restrict(int));
static_assert(!pl_is_const_volatile_atomic_restrict(int const));
static_assert(!pl_is_const_volatile_atomic_restrict(int volatile));
static_assert(!pl_is_const_volatile_atomic_restrict(int const volatile));
static_assert(!pl_is_const_volatile_atomic_restrict(int _Atomic));
static_assert(!pl_is_const_volatile_atomic_restrict(int const _Atomic));
static_assert(!pl_is_const_volatile_atomic_restrict(int volatile _Atomic));
static_assert(!pl_is_const_volatile_atomic_restrict(int const volatile _Atomic));
static_assert(!pl_is_const_volatile_atomic_restrict(int* restrict));
static_assert(!pl_is_const_volatile_atomic_restrict(int* const restrict));
static_assert(!pl_is_const_volatile_atomic_restrict(int* volatile restrict));
static_assert(!pl_is_const_volatile_atomic_restrict(int* const volatile restrict));
#ifndef __clang__
static_assert(!pl_is_const_volatile_atomic_restrict(int* _Atomic restrict));
static_assert(!pl_is_const_volatile_atomic_restrict(int* const _Atomic restrict));
static_assert(!pl_is_const_volatile_atomic_restrict(int* volatile _Atomic restrict));
static_assert(pl_is_const_volatile_atomic_restrict(int* const volatile _Atomic restrict));
#endif

static_assert(pl_is_same(pl_add_const(int), int const));
static_assert(pl_is_same(pl_add_const(int const), int const));
static_assert(pl_is_same(pl_add_const(int volatile), int const volatile));
static_assert(pl_is_same(pl_add_const(int const volatile), int const volatile));
static_assert(pl_is_same(pl_add_const(int _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_add_const(int const _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_add_const(int volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const(int* restrict), int* const restrict));
static_assert(pl_is_same(pl_add_const(int* const restrict), int* const restrict));
static_assert(pl_is_same(pl_add_const(int* volatile restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const(int* const volatile restrict), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_add_const(int* _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const(int* const _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const(int* volatile _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#endif

static_assert(pl_is_same(pl_add_volatile(int), int volatile));
static_assert(pl_is_same(pl_add_volatile(int const), int const volatile));
static_assert(pl_is_same(pl_add_volatile(int volatile), int volatile));
static_assert(pl_is_same(pl_add_volatile(int const volatile), int const volatile));
static_assert(pl_is_same(pl_add_volatile(int _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile(int const _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile(int volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile(int* restrict), int* volatile restrict));
static_assert(pl_is_same(pl_add_volatile(int* const restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_volatile(int* volatile restrict), int* volatile restrict));
static_assert(pl_is_same(pl_add_volatile(int* const volatile restrict), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_add_volatile(int* _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile(int* const _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile(int* volatile _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#endif

static_assert(pl_is_same(pl_add_const_volatile(int), int const volatile));
static_assert(pl_is_same(pl_add_const_volatile(int const), int const volatile));
static_assert(pl_is_same(pl_add_const_volatile(int volatile), int const volatile));
static_assert(pl_is_same(pl_add_const_volatile(int const volatile), int const volatile));
static_assert(pl_is_same(pl_add_const_volatile(int _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile(int const _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile(int volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile(int* restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile(int* const restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile(int* volatile restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile(int* const volatile restrict), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_add_const_volatile(int* _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile(int* const _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile(int* volatile _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#endif

static_assert(pl_is_same(pl_add_atomic(int), int _Atomic));
static_assert(pl_is_same(pl_add_atomic(int const), int const _Atomic));
static_assert(pl_is_same(pl_add_atomic(int volatile), int volatile _Atomic));
static_assert(pl_is_same(pl_add_atomic(int const volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_atomic(int _Atomic), int _Atomic));
static_assert(pl_is_same(pl_add_atomic(int const _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_add_atomic(int volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_add_atomic(int const volatile _Atomic), int const volatile _Atomic));
#ifndef __clang__
static_assert(pl_is_same(pl_add_atomic(int* restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic(int* const restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic(int* volatile restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic(int* const volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic(int* _Atomic restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic(int* const _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic(int* volatile _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#else
static_assert(pl_is_same(pl_add_atomic(int* restrict), int* restrict));
static_assert(pl_is_same(pl_add_atomic(int* const restrict), int* const restrict));
static_assert(pl_is_same(pl_add_atomic(int* volatile restrict), int* volatile restrict));
static_assert(pl_is_same(pl_add_atomic(int* const volatile restrict), int* const volatile restrict));
#endif

static_assert(pl_is_same(pl_add_const_atomic(int), int const _Atomic));
static_assert(pl_is_same(pl_add_const_atomic(int const), int const _Atomic));
static_assert(pl_is_same(pl_add_const_atomic(int volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_atomic(int const volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_atomic(int _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_add_const_atomic(int const _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_add_const_atomic(int volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_atomic(int const volatile _Atomic), int const volatile _Atomic));
#ifndef __clang__
static_assert(pl_is_same(pl_add_const_atomic(int* restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic(int* const restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic(int* volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic(int* const volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic(int* _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic(int* const _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic(int* volatile _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#else
static_assert(pl_is_same(pl_add_const_atomic(int* restrict), int* const restrict));
static_assert(pl_is_same(pl_add_const_atomic(int* const restrict), int* const restrict));
static_assert(pl_is_same(pl_add_const_atomic(int* volatile restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_atomic(int* const volatile restrict), int* const volatile restrict));
#endif

static_assert(pl_is_same(pl_add_volatile_atomic(int), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic(int const), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic(int volatile), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic(int const volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic(int _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic(int const _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic(int volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic(int const volatile _Atomic), int const volatile _Atomic));
#ifndef __clang__
static_assert(pl_is_same(pl_add_volatile_atomic(int* restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic(int* const restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic(int* volatile restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic(int* const volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic(int* _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic(int* const _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic(int* volatile _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#else
static_assert(pl_is_same(pl_add_volatile_atomic(int* restrict), int* volatile restrict));
static_assert(pl_is_same(pl_add_volatile_atomic(int* const restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_volatile_atomic(int* volatile restrict), int* volatile restrict));
static_assert(pl_is_same(pl_add_volatile_atomic(int* const volatile restrict), int* const volatile restrict));
#endif

static_assert(pl_is_same(pl_add_const_volatile_atomic(int), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int const), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int const volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int const _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int const volatile _Atomic), int const volatile _Atomic));
#ifndef __clang__
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* const restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* const volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* const _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* volatile _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#else
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* const restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* volatile restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic(int* const volatile restrict), int* const volatile restrict));
#endif

#ifdef __GNUC__
static_assert(pl_is_same(pl_add_restrict(int), int));
static_assert(pl_is_same(pl_add_restrict(int const), int const));
static_assert(pl_is_same(pl_add_restrict(int volatile), int volatile));
static_assert(pl_is_same(pl_add_restrict(int const volatile), int const volatile));
static_assert(pl_is_same(pl_add_restrict(int _Atomic), int _Atomic));
static_assert(pl_is_same(pl_add_restrict(int const _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_add_restrict(int volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_add_restrict(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_restrict(int*), int* restrict));
static_assert(pl_is_same(pl_add_restrict(int* const), int* const restrict));
static_assert(pl_is_same(pl_add_restrict(int* volatile), int* volatile restrict));
static_assert(pl_is_same(pl_add_restrict(int* const volatile), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_add_restrict(int* _Atomic), int* _Atomic restrict));
static_assert(pl_is_same(pl_add_restrict(int* const _Atomic), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_restrict(int* volatile _Atomic), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_restrict(int* const volatile _Atomic), int* const volatile _Atomic restrict));
#endif
static_assert(pl_is_same(pl_add_restrict(int* restrict), int* restrict));
static_assert(pl_is_same(pl_add_restrict(int* const restrict), int* const restrict));
static_assert(pl_is_same(pl_add_restrict(int* volatile restrict), int* volatile restrict));
static_assert(pl_is_same(pl_add_restrict(int* const volatile restrict), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_add_restrict(int* _Atomic restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_add_restrict(int* const _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_restrict(int* volatile _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_restrict(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#endif
#endif

#ifdef __GNUC__
static_assert(pl_is_same(pl_add_const_restrict(int), int const));
static_assert(pl_is_same(pl_add_const_restrict(int const), int const));
static_assert(pl_is_same(pl_add_const_restrict(int volatile), int const volatile));
static_assert(pl_is_same(pl_add_const_restrict(int const volatile), int const volatile));
static_assert(pl_is_same(pl_add_const_restrict(int _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_add_const_restrict(int const _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_add_const_restrict(int volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_restrict(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_restrict(int*), int* const restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* const), int* const restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* volatile), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* const volatile), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_add_const_restrict(int* _Atomic), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* const _Atomic), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* volatile _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* const volatile _Atomic), int* const volatile _Atomic restrict));
#endif
static_assert(pl_is_same(pl_add_const_restrict(int* restrict), int* const restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* const restrict), int* const restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* volatile restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* const volatile restrict), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_add_const_restrict(int* _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* const _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* volatile _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_restrict(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#endif
#endif

#ifdef __GNUC__
static_assert(pl_is_same(pl_add_volatile_restrict(int), int volatile));
static_assert(pl_is_same(pl_add_volatile_restrict(int const), int const volatile));
static_assert(pl_is_same(pl_add_volatile_restrict(int volatile), int volatile));
static_assert(pl_is_same(pl_add_volatile_restrict(int const volatile), int const volatile));
static_assert(pl_is_same(pl_add_volatile_restrict(int _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_restrict(int const _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_restrict(int volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_restrict(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_restrict(int*), int* volatile restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* const), int* const volatile restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* volatile), int* volatile restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* const volatile), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_add_volatile_restrict(int* _Atomic), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* const _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* volatile _Atomic), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* const volatile _Atomic), int* const volatile _Atomic restrict));
#endif
static_assert(pl_is_same(pl_add_volatile_restrict(int* restrict), int* volatile restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* const restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* volatile restrict), int* volatile restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* const volatile restrict), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_add_volatile_restrict(int* _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* const _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* volatile _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_restrict(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#endif
#endif

#ifdef __GNUC__
static_assert(pl_is_same(pl_add_const_volatile_restrict(int), int const volatile));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int const), int const volatile));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int volatile), int const volatile));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int const volatile), int const volatile));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int const _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int*), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* const), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* volatile), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* const volatile), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* const _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* volatile _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* const volatile _Atomic), int* const volatile _Atomic restrict));
#endif
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* const restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* volatile restrict), int* const volatile restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* const volatile restrict), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* const _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* volatile _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_restrict(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#endif
#endif

#if defined(__GNUC__) && !defined(__clang__)
static_assert(pl_is_same(pl_add_atomic_restrict(int), int _Atomic));
static_assert(pl_is_same(pl_add_atomic_restrict(int const), int const _Atomic));
static_assert(pl_is_same(pl_add_atomic_restrict(int volatile), int volatile _Atomic));
static_assert(pl_is_same(pl_add_atomic_restrict(int const volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_atomic_restrict(int _Atomic), int _Atomic));
static_assert(pl_is_same(pl_add_atomic_restrict(int const _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_add_atomic_restrict(int volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_add_atomic_restrict(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_atomic_restrict(int*), int* _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* const), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* volatile), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* const volatile), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* _Atomic), int* _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* const _Atomic), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* volatile _Atomic), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* const volatile _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* const restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* volatile restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* const volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* _Atomic restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* const _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* volatile _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_atomic_restrict(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#endif

#if defined(__GNUC__) && !defined(__clang__)
static_assert(pl_is_same(pl_add_const_atomic_restrict(int), int const _Atomic));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int const), int const _Atomic));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int const volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int const _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int*), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* const), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* volatile), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* const volatile), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* _Atomic), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* const _Atomic), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* volatile _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* const volatile _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* const restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* const volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* const _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* volatile _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_atomic_restrict(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#endif

#if defined(__GNUC__) && !defined(__clang__)
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int const), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int volatile), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int const volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int const _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int*), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* const), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* volatile), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* const volatile), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* _Atomic), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* const _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* volatile _Atomic), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* const volatile _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* const restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* volatile restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* const volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* const _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* volatile _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_volatile_atomic_restrict(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#endif

#if defined(__GNUC__) && !defined(__clang__)
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int const), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int const volatile), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int const _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int*), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* const), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* volatile), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* const volatile), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* const _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* volatile _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* const volatile _Atomic), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* const restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* const volatile restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* const _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* volatile _Atomic restrict), int* const volatile _Atomic restrict));
static_assert(pl_is_same(pl_add_const_volatile_atomic_restrict(int* const volatile _Atomic restrict), int* const volatile _Atomic restrict));
#endif

static_assert(pl_is_same(pl_drop_const(int), int));
static_assert(pl_is_same(pl_drop_const(int const), int));
static_assert(pl_is_same(pl_drop_const(int volatile), int volatile));
static_assert(pl_is_same(pl_drop_const(int const volatile), int volatile));
static_assert(pl_is_same(pl_drop_const(int _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const(int const _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const(int volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_drop_const(int const volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_drop_const(int* restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const(int* const restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const(int* volatile restrict), int* volatile restrict));
static_assert(pl_is_same(pl_drop_const(int* const volatile restrict), int* volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_const(int* _Atomic restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_drop_const(int* const _Atomic restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_drop_const(int* volatile _Atomic restrict), int* volatile _Atomic restrict));
static_assert(pl_is_same(pl_drop_const(int* const volatile _Atomic restrict), int* volatile _Atomic restrict));
#endif

static_assert(pl_is_same(pl_drop_volatile(int), int));
static_assert(pl_is_same(pl_drop_volatile(int const), int const));
static_assert(pl_is_same(pl_drop_volatile(int volatile), int));
static_assert(pl_is_same(pl_drop_volatile(int const volatile), int const));
static_assert(pl_is_same(pl_drop_volatile(int _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_volatile(int const _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_drop_volatile(int volatile _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_volatile(int const volatile _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_drop_volatile(int* restrict), int* restrict));
static_assert(pl_is_same(pl_drop_volatile(int* const restrict), int* const restrict));
static_assert(pl_is_same(pl_drop_volatile(int* volatile restrict), int* restrict));
static_assert(pl_is_same(pl_drop_volatile(int* const volatile restrict), int* const restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_volatile(int* _Atomic restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_drop_volatile(int* const _Atomic restrict), int* const _Atomic restrict));
static_assert(pl_is_same(pl_drop_volatile(int* volatile _Atomic restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_drop_volatile(int* const volatile _Atomic restrict), int* const _Atomic restrict));
#endif

static_assert(pl_is_same(pl_drop_const_volatile(int), int));
static_assert(pl_is_same(pl_drop_const_volatile(int const), int));
static_assert(pl_is_same(pl_drop_const_volatile(int volatile), int));
static_assert(pl_is_same(pl_drop_const_volatile(int const volatile), int));
static_assert(pl_is_same(pl_drop_const_volatile(int _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const_volatile(int const _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const_volatile(int volatile _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const_volatile(int const volatile _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const_volatile(int* restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_volatile(int* const restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_volatile(int* volatile restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_volatile(int* const volatile restrict), int* restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_const_volatile(int* _Atomic restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_drop_const_volatile(int* const _Atomic restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_drop_const_volatile(int* volatile _Atomic restrict), int* _Atomic restrict));
static_assert(pl_is_same(pl_drop_const_volatile(int* const volatile _Atomic restrict), int* _Atomic restrict));
#endif

static_assert(pl_is_same(pl_drop_atomic(int), int));
static_assert(pl_is_same(pl_drop_atomic(int const), int const));
static_assert(pl_is_same(pl_drop_atomic(int volatile), int volatile));
static_assert(pl_is_same(pl_drop_atomic(int const volatile), int const volatile));
static_assert(pl_is_same(pl_drop_atomic(int _Atomic), int));
static_assert(pl_is_same(pl_drop_atomic(int const _Atomic), int const));
static_assert(pl_is_same(pl_drop_atomic(int volatile _Atomic), int volatile));
static_assert(pl_is_same(pl_drop_atomic(int const volatile _Atomic), int const volatile));
static_assert(pl_is_same(pl_drop_atomic(int* restrict), int* restrict));
static_assert(pl_is_same(pl_drop_atomic(int* const restrict), int* const restrict));
static_assert(pl_is_same(pl_drop_atomic(int* volatile restrict), int* volatile restrict));
static_assert(pl_is_same(pl_drop_atomic(int* const volatile restrict), int* const volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_atomic(int* _Atomic restrict), int* restrict));
static_assert(pl_is_same(pl_drop_atomic(int* const _Atomic restrict), int* const restrict));
static_assert(pl_is_same(pl_drop_atomic(int* volatile _Atomic restrict), int* volatile restrict));
static_assert(pl_is_same(pl_drop_atomic(int* const volatile _Atomic restrict), int* const volatile restrict));
#endif

static_assert(pl_is_same(pl_drop_const_atomic(int), int));
static_assert(pl_is_same(pl_drop_const_atomic(int const), int));
static_assert(pl_is_same(pl_drop_const_atomic(int volatile), int volatile));
static_assert(pl_is_same(pl_drop_const_atomic(int const volatile), int volatile));
static_assert(pl_is_same(pl_drop_const_atomic(int _Atomic), int));
static_assert(pl_is_same(pl_drop_const_atomic(int const _Atomic), int));
static_assert(pl_is_same(pl_drop_const_atomic(int volatile _Atomic), int volatile));
static_assert(pl_is_same(pl_drop_const_atomic(int const volatile _Atomic), int volatile));
static_assert(pl_is_same(pl_drop_const_atomic(int* restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_atomic(int* const restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_atomic(int* volatile restrict), int* volatile restrict));
static_assert(pl_is_same(pl_drop_const_atomic(int* const volatile restrict), int* volatile restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_const_atomic(int* _Atomic restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_atomic(int* const _Atomic restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_atomic(int* volatile _Atomic restrict), int* volatile restrict));
static_assert(pl_is_same(pl_drop_const_atomic(int* const volatile _Atomic restrict), int* volatile restrict));
#endif

static_assert(pl_is_same(pl_drop_volatile_atomic(int), int));
static_assert(pl_is_same(pl_drop_volatile_atomic(int const), int const));
static_assert(pl_is_same(pl_drop_volatile_atomic(int volatile), int));
static_assert(pl_is_same(pl_drop_volatile_atomic(int const volatile), int const));
static_assert(pl_is_same(pl_drop_volatile_atomic(int _Atomic), int));
static_assert(pl_is_same(pl_drop_volatile_atomic(int const _Atomic), int const));
static_assert(pl_is_same(pl_drop_volatile_atomic(int volatile _Atomic), int));
static_assert(pl_is_same(pl_drop_volatile_atomic(int const volatile _Atomic), int const));
static_assert(pl_is_same(pl_drop_volatile_atomic(int* restrict), int* restrict));
static_assert(pl_is_same(pl_drop_volatile_atomic(int* const restrict), int* const restrict));
static_assert(pl_is_same(pl_drop_volatile_atomic(int* volatile restrict), int* restrict));
static_assert(pl_is_same(pl_drop_volatile_atomic(int* const volatile restrict), int* const restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_volatile_atomic(int* _Atomic restrict), int* restrict));
static_assert(pl_is_same(pl_drop_volatile_atomic(int* const _Atomic restrict), int* const restrict));
static_assert(pl_is_same(pl_drop_volatile_atomic(int* volatile _Atomic restrict), int* restrict));
static_assert(pl_is_same(pl_drop_volatile_atomic(int* const volatile _Atomic restrict), int* const restrict));
#endif

static_assert(pl_is_same(pl_drop_const_volatile_atomic(int), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int const), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int volatile), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int const volatile), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int _Atomic), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int const _Atomic), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int volatile _Atomic), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int const volatile _Atomic), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int* restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int* const restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int* volatile restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int* const volatile restrict), int* restrict));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int* _Atomic restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int* const _Atomic restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int* volatile _Atomic restrict), int* restrict));
static_assert(pl_is_same(pl_drop_const_volatile_atomic(int* const volatile _Atomic restrict), int* restrict));
#endif

static_assert(pl_is_same(pl_drop_restrict(int), int));
static_assert(pl_is_same(pl_drop_restrict(int const), int const));
static_assert(pl_is_same(pl_drop_restrict(int volatile), int volatile));
static_assert(pl_is_same(pl_drop_restrict(int const volatile), int const volatile));
static_assert(pl_is_same(pl_drop_restrict(int _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_restrict(int const _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_drop_restrict(int volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_drop_restrict(int const volatile _Atomic), int const volatile _Atomic));
static_assert(pl_is_same(pl_drop_restrict(int* restrict), int*));
static_assert(pl_is_same(pl_drop_restrict(int* const restrict), int* const));
static_assert(pl_is_same(pl_drop_restrict(int* volatile restrict), int* volatile));
static_assert(pl_is_same(pl_drop_restrict(int* const volatile restrict), int* const volatile));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_restrict(int* _Atomic restrict), int* _Atomic));
static_assert(pl_is_same(pl_drop_restrict(int* const _Atomic restrict), int* const _Atomic));
static_assert(pl_is_same(pl_drop_restrict(int* volatile _Atomic restrict), int* volatile _Atomic));
static_assert(pl_is_same(pl_drop_restrict(int* const volatile _Atomic restrict), int* const volatile _Atomic));
#endif

static_assert(pl_is_same(pl_drop_const_restrict(int), int));
static_assert(pl_is_same(pl_drop_const_restrict(int const), int));
static_assert(pl_is_same(pl_drop_const_restrict(int volatile), int volatile));
static_assert(pl_is_same(pl_drop_const_restrict(int const volatile), int volatile));
static_assert(pl_is_same(pl_drop_const_restrict(int _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const_restrict(int const _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const_restrict(int volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_drop_const_restrict(int const volatile _Atomic), int volatile _Atomic));
static_assert(pl_is_same(pl_drop_const_restrict(int* restrict), int*));
static_assert(pl_is_same(pl_drop_const_restrict(int* const restrict), int*));
static_assert(pl_is_same(pl_drop_const_restrict(int* volatile restrict), int* volatile));
static_assert(pl_is_same(pl_drop_const_restrict(int* const volatile restrict), int* volatile));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_const_restrict(int* _Atomic restrict), int* _Atomic));
static_assert(pl_is_same(pl_drop_const_restrict(int* const _Atomic restrict), int* _Atomic));
static_assert(pl_is_same(pl_drop_const_restrict(int* volatile _Atomic restrict), int* volatile _Atomic));
static_assert(pl_is_same(pl_drop_const_restrict(int* const volatile _Atomic restrict), int* volatile _Atomic));
#endif

static_assert(pl_is_same(pl_drop_volatile_restrict(int), int));
static_assert(pl_is_same(pl_drop_volatile_restrict(int const), int const));
static_assert(pl_is_same(pl_drop_volatile_restrict(int volatile), int));
static_assert(pl_is_same(pl_drop_volatile_restrict(int const volatile), int const));
static_assert(pl_is_same(pl_drop_volatile_restrict(int _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_volatile_restrict(int const _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_drop_volatile_restrict(int volatile _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_volatile_restrict(int const volatile _Atomic), int const _Atomic));
static_assert(pl_is_same(pl_drop_volatile_restrict(int* restrict), int*));
static_assert(pl_is_same(pl_drop_volatile_restrict(int* const restrict), int* const));
static_assert(pl_is_same(pl_drop_volatile_restrict(int* volatile restrict), int*));
static_assert(pl_is_same(pl_drop_volatile_restrict(int* const volatile restrict), int* const));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_volatile_restrict(int* _Atomic restrict), int* _Atomic));
static_assert(pl_is_same(pl_drop_volatile_restrict(int* const _Atomic restrict), int* const _Atomic));
static_assert(pl_is_same(pl_drop_volatile_restrict(int* volatile _Atomic restrict), int* _Atomic));
static_assert(pl_is_same(pl_drop_volatile_restrict(int* const volatile _Atomic restrict), int* const _Atomic));
#endif

static_assert(pl_is_same(pl_drop_const_volatile_restrict(int), int));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int const), int));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int volatile), int));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int const volatile), int));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int const _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int volatile _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int const volatile _Atomic), int _Atomic));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int* restrict), int*));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int* const restrict), int*));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int* volatile restrict), int*));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int* const volatile restrict), int*));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int* _Atomic restrict), int* _Atomic));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int* const _Atomic restrict), int* _Atomic));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int* volatile _Atomic restrict), int* _Atomic));
static_assert(pl_is_same(pl_drop_const_volatile_restrict(int* const volatile _Atomic restrict), int* _Atomic));
#endif

static_assert(pl_is_same(pl_drop_atomic_restrict(int), int));
static_assert(pl_is_same(pl_drop_atomic_restrict(int const), int const));
static_assert(pl_is_same(pl_drop_atomic_restrict(int volatile), int volatile));
static_assert(pl_is_same(pl_drop_atomic_restrict(int const volatile), int const volatile));
static_assert(pl_is_same(pl_drop_atomic_restrict(int _Atomic), int));
static_assert(pl_is_same(pl_drop_atomic_restrict(int const _Atomic), int const));
static_assert(pl_is_same(pl_drop_atomic_restrict(int volatile _Atomic), int volatile));
static_assert(pl_is_same(pl_drop_atomic_restrict(int const volatile _Atomic), int const volatile));
static_assert(pl_is_same(pl_drop_atomic_restrict(int* restrict), int*));
static_assert(pl_is_same(pl_drop_atomic_restrict(int* const restrict), int* const));
static_assert(pl_is_same(pl_drop_atomic_restrict(int* volatile restrict), int* volatile));
static_assert(pl_is_same(pl_drop_atomic_restrict(int* const volatile restrict), int* const volatile));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_atomic_restrict(int* _Atomic restrict), int*));
static_assert(pl_is_same(pl_drop_atomic_restrict(int* const _Atomic restrict), int* const));
static_assert(pl_is_same(pl_drop_atomic_restrict(int* volatile _Atomic restrict), int* volatile));
static_assert(pl_is_same(pl_drop_atomic_restrict(int* const volatile _Atomic restrict), int* const volatile));
#endif

static_assert(pl_is_same(pl_drop_const_atomic_restrict(int), int));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int const), int));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int volatile), int volatile));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int const volatile), int volatile));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int _Atomic), int));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int const _Atomic), int));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int volatile _Atomic), int volatile));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int const volatile _Atomic), int volatile));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int* restrict), int*));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int* const restrict), int*));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int* volatile restrict), int* volatile));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int* const volatile restrict), int* volatile));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int* _Atomic restrict), int*));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int* const _Atomic restrict), int*));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int* volatile _Atomic restrict), int* volatile));
static_assert(pl_is_same(pl_drop_const_atomic_restrict(int* const volatile _Atomic restrict), int* volatile));
#endif

static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int), int));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int const), int const));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int volatile), int));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int const volatile), int const));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int _Atomic), int));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int const _Atomic), int const));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int volatile _Atomic), int));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int const volatile _Atomic), int const));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int* restrict), int*));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int* const restrict), int* const));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int* volatile restrict), int*));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int* const volatile restrict), int* const));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int* _Atomic restrict), int*));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int* const _Atomic restrict), int* const));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int* volatile _Atomic restrict), int*));
static_assert(pl_is_same(pl_drop_volatile_atomic_restrict(int* const volatile _Atomic restrict), int* const));
#endif

static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int const), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int volatile), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int const volatile), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int _Atomic), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int const _Atomic), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int volatile _Atomic), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int const volatile _Atomic), int));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int* restrict), int*));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int* const restrict), int*));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int* volatile restrict), int*));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int* const volatile restrict), int*));
#ifndef __clang__
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int* _Atomic restrict), int*));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int* const _Atomic restrict), int*));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int* volatile _Atomic restrict), int*));
static_assert(pl_is_same(pl_drop_const_volatile_atomic_restrict(int* const volatile _Atomic restrict), int*));
#endif

static_assert(!pl_is_type(T));
typedef int T;
static_assert(pl_is_type(T));
