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

// Accepts an integer or floating-point argument.
// Checks if the sign bit is set.
#define pl_signbit(...) pl_choose(pl_is_int(__VA_ARGS__),(__VA_ARGS__)<0,!!signbit(pl_choose(pl_is_int(__VA_ARGS__),0.,(__VA_ARGS__))))

// Accepts an integer or floating-point argument.
// Evaluates to the absolute value of the argument.
#define pl_abs(...) pl_choose(pl_is_int(__VA_ARGS__),pl_choose((typeof(__VA_ARGS__))-1<0,(pl_make_unsigned_int(__VA_ARGS__))*(typeof(__VA_ARGS__)*)pl_abs(pl_int_width(__VA_ARGS__),(void*)&(typeof(__VA_ARGS__)){(__VA_ARGS__)}),__VA_ARGS__),fabs(__VA_ARGS__))
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
#define pl_compare(lhs, ...) pl_choose(pl_is_float((lhs)+(__VA_ARGS__)),detail_pl_compare_float((lhs),__VA_ARGS__),pl_choose(pl_is_decimal((lhs)+(__VA_ARGS__)),detail_pl_compare_decimal((lhs),__VA_ARGS__),pl_compare((typeof(lhs))-1<0,(typeof(__VA_ARGS__))-1<0,pl_int_width((lhs)+(__VA_ARGS__)),(void*)&(typeof((lhs)+(__VA_ARGS__))){(typeof((lhs)+(__VA_ARGS__)))(lhs)},(void*)&(typeof((lhs)+(__VA_ARGS__))){(typeof((lhs)+(__VA_ARGS__)))(__VA_ARGS__)})))
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
#define pl_equal(lhs, ...) (!pl_compare((lhs),__VA_ARGS__))

// Checks if the first argument is less than the second argument.
#define pl_less(lhs, ...) (pl_compare((lhs),__VA_ARGS__)<0)

// Checks if the first argument is less than or equal to the second argument.
#define pl_less_equal(lhs, ...) (pl_compare((lhs),__VA_ARGS__)<=0)

// Checks if the first argument is greater than the second argument.
#define pl_greater(lhs, ...) (pl_compare((lhs),__VA_ARGS__)>0)

// Checks if the first argument is greater than or equal to the second argument.
#define pl_greater_equal(lhs, ...) (pl_compare((lhs),__VA_ARGS__)>=0)

// Accepts two integer or floating-point arguments.
// Evaluates to the least value of the two arguments.
// If not both of the arguments' types are integers, the arguments are cast to their mutual common type.
#define pl_min(lhs, ...) (pl_choose(pl_is_float((lhs)+(__VA_ARGS__)),(typeof((lhs)+(__VA_ARGS__)))detail_pl_min_float((lhs),__VA_ARGS__),pl_choose(pl_is_decimal((lhs)+(__VA_ARGS__)),(typeof((lhs)+(__VA_ARGS__)))detail_pl_min_decimal((lhs),__VA_ARGS__),(typeof(pl_choose_type((typeof(lhs))-1<0,pl_choose((typeof(__VA_ARGS__))-1<0,(lhs)+(__VA_ARGS__),lhs),__VA_ARGS__)))*(typeof((lhs)+(__VA_ARGS__))*)pl_min((typeof(lhs))-1<0,(typeof(__VA_ARGS__))-1<0,pl_int_width((lhs)+(__VA_ARGS__)),(void*)&(typeof((lhs)+(__VA_ARGS__))){(typeof((lhs)+(__VA_ARGS__)))(lhs)},(void*)&(typeof((lhs)+(__VA_ARGS__))){(typeof((lhs)+(__VA_ARGS__)))(__VA_ARGS__)}))))
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
#define pl_max(lhs, ...) (pl_choose(pl_is_float((lhs)+(__VA_ARGS__)),(typeof((lhs)+(__VA_ARGS__)))detail_pl_max_float((lhs),__VA_ARGS__),pl_choose(pl_is_decimal((lhs)+(__VA_ARGS__)),(typeof((lhs)+(__VA_ARGS__)))detail_pl_max_decimal((lhs), __VA_ARGS__),*(typeof((lhs)+(__VA_ARGS__))*)pl_max((typeof(lhs))-1<0,(typeof(__VA_ARGS__))-1<0,pl_int_width((lhs)+(__VA_ARGS__)),(void*)&(typeof((lhs)+(__VA_ARGS__))){(typeof((lhs)+(__VA_ARGS__)))(lhs)},(void*)&(typeof((lhs)+(__VA_ARGS__))){(typeof((lhs)+(__VA_ARGS__)))(__VA_ARGS__)}))))
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
