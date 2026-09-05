#ifndef PL_MATH_H
#define PL_MATH_H

#include "./feature.h"
#include "./meta.h"
#include "./preproc.h"
#include <limits.h>
#include <math.h>
#include <stdbit.h>
#include <stddef.h>
#include <tgmath.h>

#define pl_int_width(...) \
	((size_t)_Generic(typeof_unqual(__VA_ARGS__), \
		unsigned char: UCHAR_WIDTH, \
		unsigned short: USHRT_WIDTH, \
		unsigned int: UINT_WIDTH, \
		unsigned long: ULONG_WIDTH, \
		unsigned long long: ULLONG_WIDTH, \
		signed char: SCHAR_WIDTH, \
		short: SHRT_WIDTH, \
		int: INT_WIDTH, \
		long: LONG_WIDTH, \
		long long: LLONG_WIDTH, \
		char: CHAR_WIDTH, \
		bool: BOOL_WIDTH, \
		default: _Generic(typeof_unqual(__VA_ARGS__), \
			PL_IF(pl_feature_int8)( \
				uint8_t: 8, \
				int8_t: 8, \
			)() \
			PL_IF(pl_feature_int16)( \
				uint16_t: 16, \
				int16_t: 16, \
			)() \
			PL_IF(pl_feature_int32)( \
				uint32_t: 32, \
				int32_t: 32, \
			)() \
			PL_IF(pl_feature_int64)( \
				uint64_t: 64, \
				int64_t: 64, \
			)() \
			PL_IF(pl_feature_int128)( \
				pl_uint128_t: 128, \
				pl_int128_t: 128, \
			)() \
			default: _Generic(typeof_unqual(__VA_ARGS__), \
				size_t: SIZE_WIDTH, \
				ptrdiff_t: PTRDIFF_WIDTH, \
				default: _Generic(typeof_unqual(__VA_ARGS__), \
					uintmax_t: UINTMAX_WIDTH, \
					intmax_t: INTMAX_WIDTH, \
					default: _Generic(typeof_unqual(__VA_ARGS__), \
						PL_IF(pl_feature_intptr)( \
							uintptr_t: UINTPTR_WIDTH, \
							intptr_t: INTPTR_WIDTH, \
						)() \
						default: _Generic(typeof_unqual(__VA_ARGS__), \
							uint_least8_t: UINT_LEAST8_WIDTH, \
							int_least8_t: INT_LEAST8_WIDTH, \
							default: _Generic(typeof_unqual(__VA_ARGS__), \
								uint_least16_t: UINT_LEAST16_WIDTH, \
								int_least16_t: INT_LEAST16_WIDTH, \
								default: _Generic(typeof_unqual(__VA_ARGS__), \
									uint_least32_t: UINT_LEAST32_WIDTH, \
									int_least32_t: INT_LEAST32_WIDTH, \
									default: _Generic(typeof_unqual(__VA_ARGS__), \
										uint_least64_t: UINT_LEAST64_WIDTH, \
										int_least64_t: INT_LEAST64_WIDTH, \
										default: _Generic(typeof_unqual(__VA_ARGS__), \
											uint_fast8_t: UINT_FAST8_WIDTH, \
											int_fast8_t: INT_FAST8_WIDTH, \
											default: _Generic(typeof_unqual(__VA_ARGS__), \
												uint_fast16_t: UINT_FAST16_WIDTH, \
												int_fast16_t: INT_FAST16_WIDTH, \
												default: _Generic(typeof_unqual(__VA_ARGS__), \
													uint_fast32_t: UINT_FAST32_WIDTH, \
													int_fast32_t: INT_FAST32_WIDTH, \
													default: _Generic(typeof_unqual(__VA_ARGS__), \
														uint_fast64_t: UINT_FAST64_WIDTH, \
														int_fast64_t: INT_FAST64_WIDTH, \
														default: 0 \
													) \
												) \
											) \
										) \
									) \
								) \
							) \
						) \
					) \
				) \
			) \
		) \
	))

// Accepts an integer or floating-point argument.
// Checks if the sign bit is set.
#define pl_signbit(...) \
	pl_choose(pl_is_int(__VA_ARGS__), (__VA_ARGS__) < 0, !!signbit(pl_choose(pl_is_int(__VA_ARGS__), 0.0, (__VA_ARGS__))))

// Accepts an integer or floating-point argument.
// Evaluates to the absolute value of the argument.
#define pl_abs(...) \
	pl_choose(pl_is_int(__VA_ARGS__), pl_choose((typeof(__VA_ARGS__))-1 < 0, (typeof(__VA_ARGS__))*(typeof(__VA_ARGS__)*)pl_abs(pl_int_width(__VA_ARGS__), (unsigned char*)&(typeof(__VA_ARGS__)){ (__VA_ARGS__) }), __VA_ARGS__), fabs(__VA_ARGS__))
static inline unsigned char* (pl_abs)(size_t width, unsigned char* data) {
	if (1 & (data[~-width / CHAR_BIT] >> (~-width % CHAR_BIT))) {
		bool carry = true;
		for (size_t i = 0; i <= (~-width / CHAR_BIT); ++i) {
			carry &= !(data[i] = (unsigned char)(~data[i] + carry));
		}
	}
	return data;
}


// Accepts two integer or floating-point arguments.
// Evaluates to 0, -1, or 1 if the first argument is equal to, less than, or greater than the second argument, respectively.
// If not both of the arguments' types are integers, the arguments are cast to their mutual common type.
#define pl_compare(lhs, ...) \
	pl_choose(pl_is_float((lhs) + (__VA_ARGS__)), detail_pl_compare_float((lhs), __VA_ARGS__), pl_choose(pl_is_decimal((lhs) + (__VA_ARGS__)), detail_pl_compare_decimal((lhs), __VA_ARGS__), pl_compare((typeof(lhs))-1 < 0, (typeof(__VA_ARGS__))-1 < 0, pl_int_width((lhs) + (__VA_ARGS__)), (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(lhs) }, (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(__VA_ARGS__) })))
static inline int (pl_compare)(bool lhs_signed, bool rhs_signed, size_t width, unsigned char* lhs, unsigned char* rhs) {
	bool lhs_sign = lhs_signed & (lhs[~-width / CHAR_BIT] >> (~-width % CHAR_BIT));
	bool rhs_sign = rhs_signed & (rhs[~-width / CHAR_BIT] >> (~-width % CHAR_BIT));
	if (lhs_sign != rhs_sign) {
		return rhs_sign - lhs_sign;
	}
	for (size_t i = -~(~-width / CHAR_BIT); i--;) {
		if (lhs[i] < rhs[i]) {
			return -1;
		}
		if (lhs[i] > rhs[i]) {
			return 1;
		}
	}
	return 0;
}
#ifdef __GNUC__
static inline int detail_pl_compare_float(__float128 lhs, __float128 rhs) {
	return (lhs >= rhs) - (lhs <= rhs);
}
#else
static inline int detail_pl_compare_float(long double lhs, long double rhs) {
	return (lhs >= rhs) - (lhs <= rhs);
}
#endif
#ifdef __STDC_IEC_60559_DFP__
static inline int detail_pl_compare_decimal(_Decimal128 lhs, _Decimal128 rhs) {
	return (lhs >= rhs) - (lhs <= rhs);
}
#else
static inline int detail_pl_compare_decimal(...) {
	unreachable();
}
#endif

// Checks if the first argument is equal to the second argument.
#define pl_equal(lhs, ...) \
	(!pl_compare((lhs), __VA_ARGS__))

// Checks if the first argument is less than the second argument.
#define pl_less(lhs, ...) \
	(pl_compare((lhs), __VA_ARGS__) < 0)

// Checks if the first argument is less than or equal to the second argument.
#define pl_less_equal(lhs, ...) \
	(pl_compare((lhs), __VA_ARGS__) <= 0)

// Checks if the first argument is greater than the second argument.
#define pl_greater(lhs, ...) \
	(pl_compare((lhs), __VA_ARGS__) > 0)

// Checks if the first argument is greater than or equal to the second argument.
#define pl_greater_equal(lhs, ...) \
	(pl_compare((lhs), __VA_ARGS__) >= 0)

// Accepts two integer or floating-point arguments.
// Evaluates to the least value of the two arguments.
// If not both of the arguments' types are integers, the arguments are cast to their mutual common type.
#define pl_min(lhs, ...) \
	(pl_choose(pl_is_float((lhs) + (__VA_ARGS__)), (typeof((lhs) + (__VA_ARGS__)))detail_pl_min_float((lhs), __VA_ARGS__), pl_choose(pl_is_decimal((lhs) + (__VA_ARGS__)), (typeof((lhs) + (__VA_ARGS__)))detail_pl_min_decimal((lhs), __VA_ARGS__), (typeof(pl_choose_type((typeof(lhs))-1 < 0, pl_choose((typeof(__VA_ARGS__))-1 < 0, (lhs) + (__VA_ARGS__), lhs), __VA_ARGS__)))*(typeof((lhs) + (__VA_ARGS__))*)pl_min((typeof(lhs))-1 < 0, (typeof(__VA_ARGS__))-1 < 0, pl_int_width((lhs) + (__VA_ARGS__)), (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(lhs) }, (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(__VA_ARGS__) }))))
static inline unsigned char* (pl_min)(bool lhs_signed, bool rhs_signed, size_t width, unsigned char* lhs, unsigned char* rhs) {
	return (unsigned char*[]){ lhs, lhs, rhs }[1 + (pl_compare)(lhs_signed, rhs_signed, width, lhs, rhs)];
}
#ifdef __GNUC__
static inline __float128 detail_pl_min_float(__float128 lhs, __float128 rhs) {
	return (lhs < rhs) ? lhs : rhs;
}
#else
static inline long double detail_pl_min_float(long double lhs, long double rhs) {
	return (lhs < rhs) ? lhs : rhs;
}
#endif
#ifdef __STDC_IEC_60559_DFP__
static inline _Decimal128 detail_pl_min_decimal(_Decimal128 lhs, _Decimal128 rhs) {
	return (lhs < rhs) ? lhs : rhs;
}
#else
static inline int detail_pl_min_decimal(...) {
	unreachable();
}
#endif

// Accepts two integer or floating-point arguments.
// Evaluates to the greatest value of the two arguments.
// If not both of the arguments' types are integers, the arguments are cast to their mutual common type.
#define pl_max(lhs, ...) \
	(pl_choose(pl_is_float((lhs) + (__VA_ARGS__)), (typeof((lhs) + (__VA_ARGS__)))detail_pl_max_float((lhs), __VA_ARGS__), pl_choose(pl_is_decimal((lhs) + (__VA_ARGS__)), (typeof((lhs) + (__VA_ARGS__)))detail_pl_max_decimal((lhs), __VA_ARGS__), *(typeof((lhs) + (__VA_ARGS__))*)pl_max((typeof(lhs))-1 < 0, (typeof(__VA_ARGS__))-1 < 0, pl_int_width((lhs) + (__VA_ARGS__)), (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(lhs) }, (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(__VA_ARGS__) }))))
static inline unsigned char* (pl_max)(bool lhs_signed, bool rhs_signed, size_t width, unsigned char* lhs, unsigned char* rhs) {
	return (unsigned char*[]){ rhs, lhs, lhs }[1 + (pl_compare)(lhs_signed, rhs_signed, width, lhs, rhs)];
}
#ifdef __GNUC__
static inline __float128 detail_pl_max_float(__float128 lhs, __float128 rhs) {
	return (lhs < rhs) ? rhs : lhs;
}
#else
static inline long double detail_pl_max_float(long double lhs, long double rhs) {
	return (lhs < rhs) ? rhs : lhs;
}
#endif
#ifdef __STDC_IEC_60559_DFP__
static inline _Decimal128 detail_pl_max_decimal(_Decimal128 lhs, _Decimal128 rhs) {
	return (lhs < rhs) ? rhs : lhs;
}
#else
static inline int detail_pl_max_decimal(...) {
	unreachable();
}
#endif

#endif
