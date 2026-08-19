#ifndef PL_MATH_H
#define PL_MATH_H

#include "./meta.h"
#include <limits.h>
#include <math.h>
#include <stdbit.h>
#include <stddef.h>
#include <tgmath.h>

// Evaluates to the width of the integer argument.
#define pl_int_width(...) \
	pl_int_width(sizeof(__VA_ARGS__), (unsigned char*)&(typeof(__VA_ARGS__)){ (typeof(__VA_ARGS__))-1 })
static inline size_t (pl_int_width)(size_t size, unsigned char* max) {
	for (size_t i = size; i--;) {
		if (size_t bits = stdc_trailing_ones(max[i])) {
			return i * CHAR_BIT + bits;
		}
	}
	return 0;
}

// Checks if the sign bit is set on the argument.
// If the argument's type is not an integer, calls signbit().
#define pl_signbit(...) \
	pl_choose(pl_is_int(__VA_ARGS__), (__VA_ARGS__) < 0, !!signbit(pl_choose(pl_is_int(__VA_ARGS__), 0.0, (__VA_ARGS__))))

// Evaluates to the absolute value of the argument.
// If the argument's type is not an integer, calls generic fabs().
#define pl_abs(...) \
	pl_choose(pl_is_int(__VA_ARGS__), pl_choose((typeof(__VA_ARGS__))-1 < 0, *(typeof(__VA_ARGS__)*)pl_abs(sizeof(__VA_ARGS__), (unsigned char*)&(typeof(__VA_ARGS__)){ (__VA_ARGS__) }), __VA_ARGS__), fabs(__VA_ARGS__))
[[maybe_unused]] static inline unsigned char* (pl_abs)(size_t size, unsigned char* data) {
	if (data[size - 1] & ~((unsigned char)-1 >> 1)) {
		unsigned char carry = 1;
		for (size_t i = 0; i < size; ++i) {
			carry &= !(data[i] = (unsigned char)(~data[i] + carry));
		}
	}
	return data;
}

// Evaluates to 0, -1, or 1, if the first argument is equal to, less than, or greater than the second argument.
// If not both of the arguments' types are integers, each is cast to their mutual common type.
#define pl_compare(lhs, ...) \
	pl_choose(pl_is_float((lhs) + (__VA_ARGS__)), detail_pl_compare_float((lhs), __VA_ARGS__), pl_choose(pl_is_decimal((lhs) + (__VA_ARGS__)), detail_pl_compare_decimal((lhs), __VA_ARGS__), pl_compare((typeof(lhs))-1 < 0, (typeof(__VA_ARGS__))-1 < 0, sizeof((lhs) + (__VA_ARGS__)), (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(lhs) }, (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(__VA_ARGS__) }, (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))-1 })))
static inline int (pl_compare)(bool lhs_signed, bool rhs_signed, size_t size, unsigned char* lhs, unsigned char* rhs, unsigned char* max) {
	for (size_t i = size; i--;) {
		if (max[i]) {
			bool lhs_sign = lhs_signed && (stdc_leading_zeros(lhs[i]) == stdc_leading_zeros(max[i]));
			bool rhs_sign = rhs_signed && (stdc_leading_zeros(rhs[i]) == stdc_leading_zeros(max[i]));
			if (lhs_sign != rhs_sign) {
				return rhs_sign - lhs_sign;
			}
			break;
		}
	}
	for (size_t i = size; i--;) {
		if (lhs[i] < rhs[i]) {
			return -1;
		}
		if (rhs[i] < lhs[i]) {
			return 1;
		}
	}
	return 0;
}
#ifdef __GNUC__
static inline int detail_pl_compare_float(__float128 lhs, __float128 rhs) {
	return (rhs <= lhs) - (lhs <= rhs);
}
#else
static inline int detail_pl_compare_float(long double lhs, long double rhs) {
	return (rhs <= lhs) - (lhs <= rhs);
}
#endif
#ifdef __STDC_IEC_60559_DFP__
static inline int detail_pl_compare_decimal(_Decimal128 lhs, _Decimal128 rhs) {
	return (rhs <= lhs) - (lhs <= rhs);
}
#else
static inline int detail_pl_compare_decimal(...) {
	unreachable();
}
#endif

// Checks if the first argument is equal to the second argument.
#define pl_equal(lhs, ...) \
	(!pl_compare(lhs, __VA_ARGS__))

// Checks if the first argument is less than the second argument.
#define pl_less(lhs, ...) \
	(pl_compare(lhs, __VA_ARGS__) < 0)

// Checks if the first argument is less than or equal to the second argument.
#define pl_less_equal(lhs, ...) \
	(pl_compare(lhs, __VA_ARGS__) <= 0)

// Checks if the first argument is greater than the second argument.
#define pl_greater(lhs, ...) \
	(pl_compare(lhs, __VA_ARGS__) > 0)

// Checks if the first argument is greater than or equal to the second argument.
#define pl_greater_equal(lhs, ...) \
	(pl_compare(lhs, __VA_ARGS__) >= 0)

// Evaluates to the least value of the two arguments.
// If not both of the arguments' types are integers, each is cast to their mutual common type.
#define pl_min(lhs, ...) \
	(pl_choose(pl_is_float((lhs) + (__VA_ARGS__)), (typeof((lhs) + (__VA_ARGS__)))detail_pl_min_float((lhs), __VA_ARGS__), pl_choose(pl_is_decimal((lhs) + (__VA_ARGS__)), (typeof((lhs) + (__VA_ARGS__)))detail_pl_min_decimal((lhs), __VA_ARGS__), (typeof(pl_choose_type((typeof(lhs))-1 < 0, pl_choose((typeof(__VA_ARGS__))-1 < 0, (lhs) + (__VA_ARGS__), lhs), __VA_ARGS__)))*(typeof((lhs) + (__VA_ARGS__))*)pl_min((typeof(lhs))-1 < 0, (typeof(__VA_ARGS__))-1 < 0, sizeof((lhs) + (__VA_ARGS__)), (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(lhs) }, (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(__VA_ARGS__) }, (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))-1 }))))
[[maybe_unused]] static inline unsigned char* (pl_min)(bool lhs_signed, bool rhs_signed, size_t size, unsigned char* lhs, unsigned char* rhs, unsigned char* max) {
	for (size_t i = size; i--;) {
		if (max[i]) {
			bool lhs_sign = lhs_signed && (stdc_leading_zeros(lhs[i]) == stdc_leading_zeros(max[i]));
			bool rhs_sign = rhs_signed && (stdc_leading_zeros(rhs[i]) == stdc_leading_zeros(max[i]));
			if (lhs_sign != rhs_sign) {
				return lhs_sign ? lhs : rhs;
			}
			break;
		}
	}
	for (size_t i = size; i--;) {
		if (lhs[i] < rhs[i]) {
			return lhs;
		}
		if (rhs[i] < lhs[i]) {
			return rhs;
		}
	}
	return lhs;
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

// Evaluates to the greatest value of the two integer or floating-point arguments.
// If not both of the arguments' types are integers, each is cast to their mutual common type.
#define pl_max(lhs, ...) \
	(pl_choose(pl_is_float((lhs) + (__VA_ARGS__)), (typeof((lhs) + (__VA_ARGS__)))detail_pl_max_float((lhs), __VA_ARGS__), pl_choose(pl_is_decimal((lhs) + (__VA_ARGS__)), (typeof((lhs) + (__VA_ARGS__)))detail_pl_max_decimal((lhs), __VA_ARGS__), *(typeof((lhs) + (__VA_ARGS__))*)pl_max((typeof(lhs))-1 < 0, (typeof(__VA_ARGS__))-1 < 0, sizeof((lhs) + (__VA_ARGS__)), (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(lhs) }, (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))(__VA_ARGS__) }, (unsigned char*)&(typeof((lhs) + (__VA_ARGS__))){ (typeof((lhs) + (__VA_ARGS__)))-1 }))))
[[maybe_unused]] static inline unsigned char* (pl_max)(bool lhs_signed, bool rhs_signed, size_t size, unsigned char* lhs, unsigned char* rhs, unsigned char* max) {
	for (size_t i = size; i--;) {
		if (max[i]) {
			bool lhs_sign = lhs_signed && (stdc_leading_zeros(lhs[i]) == stdc_leading_zeros(max[i]));
			bool rhs_sign = rhs_signed && (stdc_leading_zeros(rhs[i]) == stdc_leading_zeros(max[i]));
			if (lhs_sign != rhs_sign) {
				return lhs_sign ? rhs : lhs;
			}
			break;
		}
	}
	for (size_t i = size; i--;) {
		if (lhs[i] < rhs[i]) {
			return rhs;
		}
		if (rhs[i] < lhs[i]) {
			return lhs;
		}
	}
	return lhs;
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
