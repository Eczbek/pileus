#include <pl/math.h>
#include <pl/print.h>
#include <limits.h>
#include <stdio.h>

#define TEST_SIGNBIT(/*VALUE*/...) \
	{ auto x = pl_signbit(__VA_ARGS__); pl_print("signbit({}) -> {}\n", #__VA_ARGS__, x); }

#define TEST_ABS(/*VALUE*/...) \
	{ auto x = pl_abs(__VA_ARGS__); pl_print("abs({}) -> {}\n", #__VA_ARGS__, x); }

#define TEST_COMPARE(LHS, /*RHS*/...) \
	{ auto x = pl_compare((LHS), __VA_ARGS__); pl_print("{} {} {}\n", #LHS, "<=>"[x + 1], #__VA_ARGS__); }

#define TEST_MIN(LHS, /*RHS*/...) \
	{ auto x = pl_min((LHS), __VA_ARGS__); pl_print("min({}, {}) -> {}\n", #LHS, #__VA_ARGS__, x); }

#define TEST_MAX(LHS, /*RHS*/...) \
	{ auto x = pl_max((LHS), __VA_ARGS__); pl_print("max({}, {}) -> {}\n", #LHS, #__VA_ARGS__, x); }

#define TEST_CLAMP(VALUE, MIN, /*MAX*/...) \
	{ auto x = pl_clamp((VALUE), (MIN), __VA_ARGS__); pl_print("clamp({}, {}, {}) -> {}\n", #VALUE, #MIN, #__VA_ARGS__, x); }

int main() {
	TEST_SIGNBIT(0);
	TEST_SIGNBIT(1);
	TEST_SIGNBIT(-1);
	TEST_SIGNBIT(INT_MIN);
	TEST_SIGNBIT(1.0);
	TEST_SIGNBIT(-1.0);

	puts("-------------");

	TEST_ABS(5);
	TEST_ABS(-5);
	TEST_ABS(5u);
	TEST_ABS(INT_MIN);
	TEST_ABS(5.0);
	TEST_ABS(-5.0);

	puts("-------------");

	TEST_COMPARE(0, 0);
	TEST_COMPARE(1, 0);
	TEST_COMPARE(0, 1);

	TEST_COMPARE(-1, 0);
	TEST_COMPARE(-5, 5u);
	TEST_COMPARE(5u, -5);

	TEST_COMPARE(INT_MIN, (unsigned)INT_MIN);
	TEST_COMPARE((char)0, 0ull);
	TEST_COMPARE((char)-1, ULLONG_MAX);
	TEST_COMPARE(LLONG_MAX, (ULLONG_MAX >> 1));
	TEST_COMPARE(SCHAR_MIN, LLONG_MIN);

	TEST_COMPARE('0', '1');
	TEST_COMPARE(1, -1.0);

	puts("-------------");

	TEST_MIN(0, 0);
	TEST_MIN(1, 0);
	TEST_MIN(0, 1);

	TEST_MIN(-1, 0);
	TEST_MIN(-5, 5u);
	TEST_MIN(5u, -5);

	TEST_MIN(INT_MIN, (unsigned)INT_MIN);
	TEST_MIN((signed char)0, 0ull);
	TEST_MIN((signed char)-2, ULLONG_MAX);
	TEST_MIN(LLONG_MAX, (ULLONG_MAX >> 1));
	TEST_MIN(SCHAR_MIN, LLONG_MIN);

	TEST_MIN(1, -1.0);

	puts("-------------");

	TEST_MAX(0, 0);
	TEST_MAX(1, 0);
	TEST_MAX(0, 1);

	TEST_MAX(-1, 0);
	TEST_MAX(-5, 5u);
	TEST_MAX(5u, -5);

	TEST_MAX(INT_MIN, (unsigned)INT_MIN);
	TEST_MAX((signed char)0, 0ull);
	TEST_MAX((signed char)-2, ULLONG_MAX);
	TEST_MAX(LLONG_MAX, (ULLONG_MAX >> 1));
	TEST_MAX(SCHAR_MIN, LLONG_MIN);

	TEST_MAX(1, -1.0);

	puts("-------------");

	TEST_CLAMP(0.5, 0, 1);
	TEST_CLAMP(-0.5, 0, 1);
	TEST_CLAMP(1.5, 0, 1);
	TEST_CLAMP(-1, 0u, 1u);
}
