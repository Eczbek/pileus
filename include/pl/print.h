#ifndef PL_PRINT_H
#define PL_PRINT_H

#include "./meta.h"
#include "./preproc.h"
#include "./static_assert.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Accepts a format string and arguments to format.
// Evaluates to the number of characters formatted.
// Placeholders in the format string are represented by `{}` and may be escaped with `{{` and `}}`.
// The number of placeholders must match the number of arguments passed.
#define pl_print(format, /*args*/...) pl_print_to(stdout,(format),__VA_ARGS__)

// Accepts a FILE* stream, a format string, and arguments to format.
// Evaluates to the number of characters formatted.
#define pl_print_to(stream, format, /*args*/...) detail_pl_format_to(__FILE__,__LINE__,(FILE*)(stream),1,(size_t)-1,(format),PL_EACH(detail_pl_format_assign,__VA_ARGS__)detail_pl_format_id_sentinel)

// Accepts a char* buffer, a format string, and arguments to format.
// Evaluates to the number of characters formatted, including the terminator.
#define pl_format_to(buffer, format, /*args*/...) pl_format_to_sized((buffer),(size_t)-1,(format),__VA_ARGS__)

// Accepts a char* buffer, a size_t expression representing the buffer's maximum size, a format string, and arguments to format.
// Evaluates to the number of characters formatted, including the terminator.
#define pl_format_to_sized(buffer, size, format, /*args*/...) detail_pl_format_to(__FILE__,__LINE__,(char*)(buffer),0,(size),(format),PL_EACH(detail_pl_format_assign,__VA_ARGS__)detail_pl_format_id_sentinel)

// Accepts a format string and arguments to format.
// Evaluates to the number of characters formatted, including the terminator.
#define pl_format_size(format, /*args*/...) pl_format_to(0,(format),__VA_ARGS__)

enum {
	detail_pl_format_id_sentinel,
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
	detail_pl_format_id_address,
	detail_pl_format_id_unknown
};

#define detail_pl_format_id(...) _Generic(pl_fake_unqual(__VA_ARGS__),unsigned char:detail_pl_format_id_unsigned_char,unsigned short:detail_pl_format_id_unsigned_short,typeof(0u):detail_pl_format_id_unsigned_int,typeof(0ul):detail_pl_format_id_unsigned_long,typeof(0ull):detail_pl_format_id_unsigned_long_long,signed char:detail_pl_format_id_signed_char,short:detail_pl_format_id_short,int:detail_pl_format_id_int,long:detail_pl_format_id_long,long long:detail_pl_format_id_long_long,float:detail_pl_format_id_float,double:detail_pl_format_id_double,long double:detail_pl_format_id_long_double,char:detail_pl_format_id_char,bool:detail_pl_format_id_bool,char*:detail_pl_format_id_string,const char*:detail_pl_format_id_string,void*:detail_pl_format_id_address,const void*:detail_pl_format_id_address,default:detail_pl_format_id_unknown)

#define detail_pl_format_assign(...) (pl_static_assert(detail_pl_format_id(__VA_ARGS__)!=detail_pl_format_id_unknown,"unformattable argument: "#__VA_ARGS__),detail_pl_format_id(__VA_ARGS__)),(__VA_ARGS__),

size_t detail_pl_format_check_impl(const char* sloc_file, size_t sloc_line, const char* format, size_t i, va_list args) {
	for (;; ++i) {
		if (!format[i]) {
			fprintf(stderr, "%s:%zu: unmatched '{' in format ", sloc_file, sloc_line);
			return (size_t)-1;
		} else if (format[i] == '}') {
			if (format[i + 1] != '}') {
				break;
			}
			++i;
		} else if (format[i] == '{') {
			if (format[i + 1] != '{') {
				if (!~(i = detail_pl_format_check_impl(sloc_file, sloc_line, format, i + 1, args))) {
					return i;
				}
				continue;
			}
			++i;
		}
	}
	switch (va_arg(args, int)) {
		case detail_pl_format_id_sentinel:
			fprintf(stderr, "%s:%zu: too few arguments for format ", sloc_file, sloc_line);
			return (size_t)-1;
		case detail_pl_format_id_unsigned_char:
		case detail_pl_format_id_unsigned_short:
		case detail_pl_format_id_signed_char:
		case detail_pl_format_id_short:
		case detail_pl_format_id_int:
		case detail_pl_format_id_char:
		case detail_pl_format_id_bool:
			va_arg(args, int);
			break;
		case detail_pl_format_id_unsigned_int:
			va_arg(args, unsigned int);
			break;
		case detail_pl_format_id_unsigned_long:
			va_arg(args, unsigned long);
			break;
		case detail_pl_format_id_unsigned_long_long:
			va_arg(args, unsigned long long);
			break;
		case detail_pl_format_id_long:
			va_arg(args, long long);
			break;
		case detail_pl_format_id_long_long:
			va_arg(args, unsigned long long);
			break;
		case detail_pl_format_id_float:
		case detail_pl_format_id_double:
			va_arg(args, double);
			break;
		case detail_pl_format_id_long_double:
			va_arg(args, long double);
			break;
		case detail_pl_format_id_string:
			va_arg(args, const char*);
			break;
		case detail_pl_format_id_address:
			va_arg(args, const void*);
			break;
		default:
			unreachable();
	}
	return i;
}

bool detail_pl_format_check(const char* sloc_file, size_t sloc_line, const char* format, va_list args) {
	size_t i = 0;
	for (; format[i]; ++i) {
		if (format[i] == '}') {
			if (format[i + 1] != '}') {
				fprintf(stderr, "%s:%zu: unmatched '}' in format ", sloc_file, sloc_line);
				i = (size_t)-1;
				break;
			}
			++i;
		} else if (format[i] == '{') {
			if (format[i + 1] != '{') {
				if (!~(i = detail_pl_format_check_impl(sloc_file, sloc_line, format, i + 1, args))) {
					break;
				}
				continue;
			}
			++i;
		}
	}
	if (~i) {
		if (va_arg(args, int) == detail_pl_format_id_sentinel) {
			return true;
		}
		fprintf(stderr, "%s:%zu: too many arguments for format ", sloc_file, sloc_line);
	}
	fputc('"', stderr);
	for (; *format; ++format) {
		char c = *format;
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
	fprintf(stderr, "\"\n");
	return false;
}

size_t detail_pl_format_impl(void* buffer, bool is_stream, size_t* size, size_t max_size, const char* format, size_t i, va_list args) {
	for (; format[i]; ++i) {
		if (format[i] == '}') {
			size_t count = 1;
			while (format[i + count] == '}') {
				++count;
			}
			if (count % 2) {
				break;
			}
			++i;
		} else if (format[i] == '{') {
			if (format[i + 1] != '{') {
				i = detail_pl_format_impl(nullptr, false, size, (size_t)-1, format, i + 1, args);
				continue;
			}
			++i;
		}
	}
	#define detail_pl_format_arg(FORMAT, ARG) do { \
		if ((*size + !is_stream) < max_size) { \
			if (buffer) { \
				if (is_stream) { \
					*size += (size_t)fprintf(buffer, (FORMAT), (ARG)); \
				} else { \
					*size += (size_t)snprintf((char*)buffer + *size, max_size - *size, (FORMAT), (ARG)); \
					if (i >= ~-max_size) { \
						*size = ~-max_size; \
					} \
				} \
			} else { \
				*size += (size_t)snprintf(nullptr, 0, (FORMAT), (ARG)); \
			} \
		} \
	} while (0)
	switch (va_arg(args, int)) {
		case detail_pl_format_id_unsigned_char:
		case detail_pl_format_id_unsigned_short:
			detail_pl_format_arg("%u", (unsigned int)va_arg(args, int));
			break;
		case detail_pl_format_id_unsigned_int:
			detail_pl_format_arg("%u", va_arg(args, unsigned int));
			break;
		case detail_pl_format_id_unsigned_long:
			detail_pl_format_arg("%lu", va_arg(args, unsigned long));
			break;
		case detail_pl_format_id_unsigned_long_long:
			detail_pl_format_arg("%llu", va_arg(args, unsigned long long));
			break;
		case detail_pl_format_id_signed_char:
		case detail_pl_format_id_short:
		case detail_pl_format_id_int:
			detail_pl_format_arg("%i", va_arg(args, int));
			break;
		case detail_pl_format_id_long:
			detail_pl_format_arg("%li", va_arg(args, long));
			break;
		case detail_pl_format_id_long_long:
			detail_pl_format_arg("%lli", va_arg(args, long long));
			break;
		case detail_pl_format_id_float:
		case detail_pl_format_id_double:
			detail_pl_format_arg("%f", va_arg(args, double));
			break;
		case detail_pl_format_id_long_double:
			detail_pl_format_arg("%Lf", va_arg(args, long double));
			break;
		case detail_pl_format_id_char:
			detail_pl_format_arg("%c", va_arg(args, int));
			break;
		case detail_pl_format_id_bool:
			detail_pl_format_arg("%s", va_arg(args, int) ? "true" : "false");
			break;
		case detail_pl_format_id_string:
			detail_pl_format_arg("%s", va_arg(args, const char*));
			break;
		case detail_pl_format_id_address:
			detail_pl_format_arg("%p", va_arg(args, const void*));
			break;
		default:
			unreachable();
	}
	return i;
}

size_t detail_pl_format_to(const char* sloc_file, size_t sloc_line, void* buffer, bool is_stream, size_t max_size, const char* format, ...) {
	va_list args;
	va_start(args, format);
	if (!detail_pl_format_check(sloc_file, sloc_line, format, args)) {
		abort();
	}
	va_end(args);
	va_start(args, format);
	size_t size = 0;
	for (size_t i = 0; format[i]; ++i) {
		if (format[i] == '}') {
			if (format[i + 1] == '}') {
				++i;
			}
		} else if (format[i] == '{') {
			if (format[i + 1] != '{') {
				if (!format[i = detail_pl_format_impl(buffer, is_stream, &size, max_size, format, i + 1, args)]) {
					break;
				}
				continue;
			}
			++i;
		}
		if ((size + !is_stream) < max_size) {
			if (buffer) {
				if (is_stream) {
					fputc(format[i], buffer);
				} else {
					((char*)buffer)[size] = format[i];
				}
			}
			++size;
		}
	}
	va_end(args);
	return size;
}

#endif
