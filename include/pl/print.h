#ifndef PL_PRINT_H
#define PL_PRINT_H

#include "./meta.h"
#include "./preproc.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

// Accepts a format string and arguments to format.
// Evaluates to the number of characters formatted.
// Placeholders in the format string are represented by `%` and may be escaped with `/%`.
// The number of placeholders must match the number of arguments passed.
#define pl_print(format, ...) \
	pl_print_to(stdout, (format), __VA_ARGS__)

// Accepts a FILE* stream, a format string, and arguments to format.
// Evaluates to the number of characters formatted.
#define pl_print_to(stream, format, ...) \
	detail_pl_format_to(__FILE__, __LINE__, (FILE*)(stream), true, (size_t)-1, (format), PL_EACH(detail_pl_format_id, __VA_ARGS__) detail_pl_format_id_sentinel)

// Accepts a char* buffer, a format string, and arguments to format.
// Evaluates to the number of characters formatted, including the terminator.
#define pl_format_to(buffer, format, ...) \
	pl_format_to_sized((buffer), (size_t)-1, (format), __VA_ARGS__)

// Accepts a char* buffer, a size_t expression representing the buffer's maximum size, a format string, and arguments to format.
// Evaluates to the number of characters formatted, including the terminator.
#define pl_format_to_sized(buffer, size, format, ...) \
	detail_pl_format_to(__FILE__, __LINE__, (char*)(buffer), false, (size), (format), PL_EACH(detail_pl_format_id, __VA_ARGS__) detail_pl_format_id_sentinel)

// Accepts a format string and arguments to format.
// Evaluates to the number of characters formatted, including the terminator.
#define pl_format_size(format, ...) \
	pl_format_to(nullptr, (format), __VA_ARGS__)

enum {
	detail_pl_format_id_sentinel,
	detail_pl_format_id_unknown,
	detail_pl_format_id_unsigned_char,
	detail_pl_format_id_unsigned_short,
	detail_pl_format_id_unsigned_int,
	detail_pl_format_id_unsigned_long,
	detail_pl_format_id_unsigned_long_long,
	detail_pl_format_id_signed_char,
	detail_pl_format_id_short,
	detail_pl_format_id_int,
	detail_pl_format_id_long,
	detail_pl_format_id_long_long,
	detail_pl_format_id_float,
	detail_pl_format_id_double,
	detail_pl_format_id_long_double,
	detail_pl_format_id_char,
	detail_pl_format_id_bool,
	detail_pl_format_id_string,
	detail_pl_format_id_address
};
#define detail_pl_format_id(...) \
	_Generic(pl_fake_unqual(__VA_ARGS__), \
		unsigned char: detail_pl_format_id_unsigned_char, \
		unsigned short: detail_pl_format_id_unsigned_short, \
		unsigned int: detail_pl_format_id_unsigned_int, \
		unsigned long: detail_pl_format_id_unsigned_long, \
		unsigned long long: detail_pl_format_id_unsigned_long_long, \
		signed char: detail_pl_format_id_signed_char, \
		short: detail_pl_format_id_short, \
		int: detail_pl_format_id_int, \
		long: detail_pl_format_id_long, \
		long long: detail_pl_format_id_long_long, \
		float: detail_pl_format_id_float, \
		double: detail_pl_format_id_double, \
		long double: detail_pl_format_id_long_double, \
		char: detail_pl_format_id_char, \
		bool: detail_pl_format_id_bool, \
		char*: detail_pl_format_id_string, \
		const char*: detail_pl_format_id_string, \
		void*: detail_pl_format_id_address, \
		const void*: detail_pl_format_id_address, \
		default: detail_pl_format_id_unknown \
	), (__VA_ARGS__),
static inline size_t detail_pl_format_to(const char* sloc_file, size_t sloc_line, void* buffer, bool is_stream, size_t max_size, const char* format, ...) {
	static constexpr char placeholder = '%';
	static constexpr char escape = '/';
	va_list args;
	va_start(args, format);
	bool bad_arg = false;
	bool bad_sentinel = false;
	size_t placeholder_count = 0;
	for (size_t i = 0; !bad_arg && !bad_sentinel; ++i) {
		if (!format || !format[i]) {
			if (va_arg(args, int) != detail_pl_format_id_sentinel) {
				bad_sentinel = true;
				fprintf(stderr, "%s:%zu: too many arguments for format ", sloc_file, sloc_line);
			}
			break;
		}
		if ((i && (format[i - 1] == escape)) || (format[i] != placeholder)) {
			continue;
		}
		++placeholder_count;
		switch (va_arg(args, int)) {
			case detail_pl_format_id_sentinel:
				bad_sentinel = true;
				fprintf(stderr, "%s:%zu: too few arguments for format ", sloc_file, sloc_line);
				break;
			case detail_pl_format_id_unknown:
				bad_arg = true;
				fprintf(stderr, "%s:%zu: unprintable argument for placeholder at index %zu in format ", sloc_file, sloc_line, i);
				break;
			case detail_pl_format_id_unsigned_char:
			case detail_pl_format_id_unsigned_short:
			case detail_pl_format_id_signed_char:
			case detail_pl_format_id_short:
			case detail_pl_format_id_int:
			case detail_pl_format_id_char:
			case detail_pl_format_id_bool:
				va_arg(args, int);
				continue;
			case detail_pl_format_id_unsigned_int:
				va_arg(args, unsigned int);
				continue;
			case detail_pl_format_id_unsigned_long:
				va_arg(args, unsigned long);
				continue;
			case detail_pl_format_id_unsigned_long_long:
				va_arg(args, unsigned long long);
				continue;
			case detail_pl_format_id_long:
				va_arg(args, long long);
				continue;
			case detail_pl_format_id_long_long:
				va_arg(args, unsigned long long);
				continue;
			case detail_pl_format_id_float:
			case detail_pl_format_id_double:
				va_arg(args, double);
				continue;
			case detail_pl_format_id_long_double:
				va_arg(args, long double);
				continue;
			case detail_pl_format_id_string:
				va_arg(args, const char*);
				continue;
			case detail_pl_format_id_address:
				va_arg(args, void*);
				continue;
			default:
				unreachable();
		}
	}
	if (bad_arg || bad_sentinel) {
		va_end(args);
		fputc('"', stderr);
		for (const char* c = format; c && *c; ++c) {
			if (*c == '\a') {
				fputs("\\a", stderr);
			} else if (*c == '\b') {
				fputs("\\b", stderr);
			} else if (*c == '\f') {
				fputs("\\f", stderr);
			} else if (*c == '\n') {
				fputs("\\n", stderr);
			} else if (*c == '\r') {
				fputs("\\r", stderr);
			} else if (*c == '\t') {
				fputs("\\t", stderr);
			} else if (*c == '\v') {
				fputs("\\v", stderr);
			} else {
				fputc(*c, stderr);
			}
		}
		fputc('"', stderr);
		if (bad_sentinel) {
			fprintf(stderr, " (expects %zu argument%s)", placeholder_count, (placeholder_count == 1) ? "" : "s");
		}
		fputc('\n', stderr);
		return 0;
	}
	va_start(args, format);
	bool escaped = false;
	size_t size = 0;
	#define detail_pl_print_char(C) \
		do { \
			if ((size + !is_stream) < max_size) { \
				if (buffer) { \
					if (is_stream) { \
						fputc((C), buffer); \
					} else { \
						((char*)buffer)[size] = (C); \
					} \
				} \
				++size; \
			} \
		} while (0)
	#define detail_pl_print_one(format, ARG) \
		do { \
			if ((size + !is_stream) < max_size) { \
				if (buffer) { \
					if (is_stream) { \
						size += (size_t)fprintf(buffer, (format), (ARG)); \
					} else { \
						size += (size_t)snprintf((char*)buffer + size, max_size - size, (format), (ARG)); \
						if (size >= ~-max_size) { \
							size = ~-max_size; \
						} \
					} \
				} else { \
					size += (size_t)snprintf(nullptr, 0, (format), (ARG)); \
				} \
			} \
		} while (0)
	for (const char* c = format; c && *c; escaped = *c++ == escape) {
		if (escaped) {
			if ((*c != placeholder) && (*c != escape)) {
				detail_pl_print_char(escape);
			}
			detail_pl_print_char(*c);
		} else if (*c == placeholder) {
			switch (va_arg(args, int)) {
				case detail_pl_format_id_unsigned_char:
				case detail_pl_format_id_unsigned_short:
					detail_pl_print_one("%u", (unsigned int)va_arg(args, int));
					continue;
				case detail_pl_format_id_unsigned_int:
					detail_pl_print_one("%u", va_arg(args, unsigned int));
					continue;
				case detail_pl_format_id_unsigned_long:
					detail_pl_print_one("%lu", va_arg(args, unsigned long));
					continue;
				case detail_pl_format_id_unsigned_long_long:
					detail_pl_print_one("%llu", va_arg(args, unsigned long long));
					continue;
				case detail_pl_format_id_signed_char:
				case detail_pl_format_id_short:
				case detail_pl_format_id_int:
					detail_pl_print_one("%i", va_arg(args, int));
					continue;
				case detail_pl_format_id_long:
					detail_pl_print_one("%li", va_arg(args, long));
					continue;
				case detail_pl_format_id_long_long:
					detail_pl_print_one("%lli", va_arg(args, long long));
					continue;
				case detail_pl_format_id_float:
				case detail_pl_format_id_double:
					detail_pl_print_one("%f", va_arg(args, double));
					continue;
				case detail_pl_format_id_long_double:
					detail_pl_print_one("%Lf", va_arg(args, long double));
					continue;
				case detail_pl_format_id_char:
					detail_pl_print_one("%c", va_arg(args, int));
					continue;
				case detail_pl_format_id_bool:
					detail_pl_print_one("%s", va_arg(args, int) ? "true" : "false");
					continue;
				case detail_pl_format_id_string:
					detail_pl_print_one("%s", va_arg(args, const char*));
					continue;
				case detail_pl_format_id_address:
					detail_pl_print_one("%p", va_arg(args, void*));
					continue;
				default:
					unreachable();
			}
		} else if (*c != escape) {
			detail_pl_print_char(*c);
		}
	}
	if (escaped) {
		detail_pl_print_char(escape);
	}
	va_end(args);
	if (!is_stream && (-~size < max_size)) {
		if (buffer) {
			((char*)buffer)[size] = '\0';
		}
		++size;
	}
	return size;
}

#endif
