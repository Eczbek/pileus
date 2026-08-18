#include "../include/pl/math.h"
#include <limits.h>
#include <stdio.h>

#define TEST_INT_WIDTH(...) \
	printf("int_width(%s) -> %zu\n", #__VA_ARGS__, pl_int_width(__VA_ARGS__))

#define TEST_SIGNBIT(...) \
	printf("signbit(%s) -> %i\n", #__VA_ARGS__, pl_signbit(__VA_ARGS__))

#define TEST_ABS(...) \
	printf(_Generic(pl_abs(__VA_ARGS__), \
		double: "abs(%s) -> %f\n", \
		default: "abs(%s) -> %u\n" \
	), #__VA_ARGS__, pl_abs(__VA_ARGS__))

#define TEST_COMPARE(X, ...) \
	printf("%s %c %s\n", #X, "<=>"[pl_compare((X), __VA_ARGS__) + 1], #__VA_ARGS__)

#define TEST_MIN(X, ...) \
	printf(_Generic(pl_min((X), __VA_ARGS__), \
		int: "min(%s, %s) -> %i\n", \
		unsigned int: "min(%s, %s) -> %u\n", \
		long long: "min(%s, %s) -> %lli\n", \
		unsigned long long: "min(%s, %s) -> %llu\n", \
		char: "min(%s, %s) -> %i\n", \
		double: "min(%s, %s) -> %f\n" \
	), #X, #__VA_ARGS__, pl_min((X), __VA_ARGS__))

#define TEST_MAX(X, ...) \
	printf(_Generic(pl_max((X), __VA_ARGS__), \
		int: "max(%s, %s) -> %i\n", \
		unsigned int: "max(%s, %s) -> %u\n", \
		long long: "max(%s, %s) -> %lli\n", \
		unsigned long long: "max(%s, %s) -> %llu\n", \
		char: "max(%s, %s) -> %i\n", \
		double: "max(%s, %s) -> %f\n" \
	), #X, #__VA_ARGS__, pl_max((X), __VA_ARGS__))

int main() {
	TEST_INT_WIDTH(char);
	TEST_INT_WIDTH(int);
	TEST_INT_WIDTH(unsigned long long);

	puts("-------------");

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
	TEST_COMPARE((char)0, ULLONG_MAX);
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
	TEST_MIN((char)0, 0ull);
	TEST_MIN((char)-2, ULLONG_MAX);
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
	TEST_MAX((char)0, 0ull);
	TEST_MAX((char)-2, ULLONG_MAX);
	TEST_MAX(LLONG_MAX, (ULLONG_MAX >> 1));
	TEST_MAX(SCHAR_MIN, LLONG_MIN);

	TEST_MAX(1, -1.0);
}
