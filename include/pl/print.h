#ifndef PL_PRINT_H
#define PL_PRINT_H

#include "./preproc.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

// Accepts a format string and arguments to format.
// Placeholders in the format string are represented by `%` and may be escaped with `/%`.
// The number of placeholders must match the number of arguments passed.
#define pl_print(FORMAT, ...) \
	pl_fprint(stdout, (FORMAT), __VA_ARGS__)
#define pl_fprint(STREAM, FORMAT, ...) \
	pl_fprint((STREAM), (FORMAT), PL_EACH(detail_pl_print_id, __VA_ARGS__) detail_pl_print_sentinel)
enum {
	detail_pl_print_unsigned_char,
	detail_pl_print_unsigned_short,
	detail_pl_print_unsigned_int,
	detail_pl_print_unsigned_long,
	detail_pl_print_unsigned_long_long,
	detail_pl_print_signed_char,
	detail_pl_print_short,
	detail_pl_print_int,
	detail_pl_print_long,
	detail_pl_print_long_long,
	detail_pl_print_float,
	detail_pl_print_double,
	detail_pl_print_long_double,
	detail_pl_print_char,
	detail_pl_print_bool,
	detail_pl_print_string,
	detail_pl_print_address,
	detail_pl_print_unknown,
	detail_pl_print_sentinel
};
#define detail_pl_print_id(...) \
	_Generic(typeof_unqual(__VA_ARGS__), \
		unsigned char: detail_pl_print_unsigned_char, \
		unsigned short: detail_pl_print_unsigned_short, \
		unsigned int: detail_pl_print_unsigned_int, \
		unsigned long: detail_pl_print_unsigned_long, \
		unsigned long long: detail_pl_print_unsigned_long_long, \
		signed char: detail_pl_print_signed_char, \
		short: detail_pl_print_short, \
		int: detail_pl_print_int, \
		long: detail_pl_print_long, \
		long long: detail_pl_print_long_long, \
		float: detail_pl_print_float, \
		double: detail_pl_print_double, \
		long double: detail_pl_print_long_double, \
		char: detail_pl_print_char, \
		bool: detail_pl_print_bool, \
		char*: detail_pl_print_string, \
		const char*: detail_pl_print_string, \
		void*: detail_pl_print_address, \
		const void*: detail_pl_print_address, \
		default: detail_pl_print_unknown \
	), (__VA_ARGS__),
static inline bool (pl_fprint)(FILE* stream, const char* format, ...) {
	static constexpr char placeholder = '%';
	static constexpr char escape = '/';
	va_list args;
	va_start(args, format);
	for (size_t i = 0; format[i]; ++i) {
		if ((!i || (format[i - 1] != escape)) && (format[i] == placeholder)) {
			switch (va_arg(args, int)) {
				case detail_pl_print_unsigned_char:
				case detail_pl_print_unsigned_short:
				case detail_pl_print_signed_char:
				case detail_pl_print_short:
				case detail_pl_print_int:
				case detail_pl_print_char:
				case detail_pl_print_bool:
					va_arg(args, int);
					continue;
				case detail_pl_print_unsigned_int:
					va_arg(args, unsigned int);
					continue;
				case detail_pl_print_unsigned_long:
					va_arg(args, unsigned long);
					continue;
				case detail_pl_print_unsigned_long_long:
					va_arg(args, unsigned long long);
					continue;
				case detail_pl_print_long:
					va_arg(args, long long);
					continue;
				case detail_pl_print_long_long:
					va_arg(args, unsigned long long);
					continue;
				case detail_pl_print_float:
				case detail_pl_print_double:
					va_arg(args, double);
					continue;
				case detail_pl_print_long_double:
					va_arg(args, long double);
					continue;
				case detail_pl_print_string:
					va_arg(args, const char*);
					continue;
				case detail_pl_print_address:
					va_arg(args, void*);
					continue;
				case detail_pl_print_unknown:
					fprintf(stderr, "unprintable argument for placeholder at position %zu in format string ", i);
					break;
				case detail_pl_print_sentinel:
					fprintf(stderr, "no argument for placeholder at position %zu in format string ", i);
					break;
			}
			fputs("\"", stderr);
			while (*format) {
				char c = *format++;
				if (c == '\a') {
					fputs("\\a", stderr);
				} else if (c == '\b') {
					fputs("\\b", stderr);
				} else if (c == '\f') {
					fputs("\\f", stderr);
				} else if (c == '\n') {
					fputs("\\n", stderr);
				} else if (c == '\r') {
					fputs("\\r", stderr);
				} else if (c == '\t') {
					fputs("\\t", stderr);
				} else if (c == '\v') {
					fputs("\\v", stderr);
				} else {
					fputc(c, stderr);
				}
			}
			fputs("\"\n", stderr);
			va_end(args);
			return false;
		}
	}
	va_start(args, format);
	bool escaped = false;
	for (; *format; escaped = *format++ == escape) {
		if (escaped) {
			if ((*format != placeholder) && (*format != escape)) {
				putc(escape, stream);
			}
			putc(*format, stream);
		} else if (*format == placeholder) {
			switch (va_arg(args, int)) {
				case detail_pl_print_unsigned_char:
				case detail_pl_print_unsigned_short:
					fprintf(stream, "%u", (unsigned int)va_arg(args, int));
					continue;
				case detail_pl_print_unsigned_int:
					fprintf(stream, "%u", va_arg(args, unsigned int));
					continue;
				case detail_pl_print_unsigned_long:
					fprintf(stream, "%lu", va_arg(args, unsigned long));
					continue;
				case detail_pl_print_unsigned_long_long:
					fprintf(stream, "%llu", va_arg(args, unsigned long long));
					continue;
				case detail_pl_print_signed_char:
				case detail_pl_print_short:
				case detail_pl_print_int:
					fprintf(stream, "%i", va_arg(args, int));
					continue;
				case detail_pl_print_long:
					fprintf(stream, "%li", va_arg(args, long));
					continue;
				case detail_pl_print_long_long:
					fprintf(stream, "%lli", va_arg(args, long long));
					continue;
				case detail_pl_print_float:
				case detail_pl_print_double:
					fprintf(stream, "%f", va_arg(args, double));
					continue;
				case detail_pl_print_long_double:
					fprintf(stream, "%Lf", va_arg(args, long double));
					continue;
				case detail_pl_print_char:
					fprintf(stream, "%c", va_arg(args, int));
					continue;
				case detail_pl_print_bool:
					fprintf(stream, "%s", va_arg(args, int) ? "true" : "false");
					continue;
				case detail_pl_print_string:
					fprintf(stream, "%s", va_arg(args, const char*));
					continue;
				case detail_pl_print_address:
					fprintf(stream, "%p", va_arg(args, void*));
					continue;
			}
		} else if (*format != escape) {
			putc(*format, stream);
		}
	}
	if (escaped) {
		putc(escape, stream);
	}
	va_end(args);
	return true;
}

#endif
