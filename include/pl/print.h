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
#define pl_print_to(stream, format, /*args*/...) detail_pl_format_to(__FILE__,__LINE__,(FILE*)(stream),1,(size_t)-1,(format),PL_EACH(detail_pl_format_assign,__VA_ARGS__)0)

// Accepts a char* buffer, a format string, and arguments to format.
// Evaluates to the number of characters formatted, including the terminator.
#define pl_format_to(buffer, format, /*args*/...) pl_format_to_sized((buffer),(size_t)-1,(format),__VA_ARGS__)

// Accepts a char* buffer, a size_t expression representing the buffer's maximum size, a format string, and arguments to format.
// Evaluates to the number of characters formatted, including the terminator.
#define pl_format_to_sized(buffer, max_size, format, /*args*/...) detail_pl_format_to(__FILE__,__LINE__,(char*)(buffer),0,(max_size),(format),PL_EACH(detail_pl_format_assign,__VA_ARGS__)0)

// Accepts a format string and arguments to format.
// Evaluates to the number of characters formatted, including the terminator.
#define pl_format_size(format, /*args*/...) pl_format_to(0,(format),__VA_ARGS__)

#define detail_pl_format_id(...) _Generic(pl_fake_unqual(__VA_ARGS__),unsigned char:1,unsigned short:2,typeof(0u):3,typeof(0ul):4,typeof(0ull):5,signed char:6,short:7,int:8,long:9,long long:10,float:11,double:12,long double:13,char:14,bool:15,char*:16,char const*:16,void*:17,void const*:17,default:0)

#define detail_pl_format_assign(...) (pl_static_assert(detail_pl_format_id(__VA_ARGS__),"unformattable argument: "#__VA_ARGS__),detail_pl_format_id(__VA_ARGS__)),(__VA_ARGS__),

#ifndef NDEBUG
static inline size_t detail_pl_format_check_impl(char const* sloc_file, size_t sloc_line, char const* format, size_t i, va_list args) {
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
		case 0:
			fprintf(stderr, "%s:%zu: too few arguments for format ", sloc_file, sloc_line);
			return (size_t)-1;
		case 1:
		case 2:
		case 6:
		case 7:
		case 8:
		case 14:
		case 15:
			va_arg(args, int);
			break;
		case 3:
			va_arg(args, unsigned int);
			break;
		case 4:
			va_arg(args, unsigned long);
			break;
		case 5:
			va_arg(args, unsigned long long);
			break;
		case 9:
			va_arg(args, long long);
			break;
		case 10:
			va_arg(args, unsigned long long);
			break;
		case 11:
		case 12:
			va_arg(args, double);
			break;
		case 13:
			va_arg(args, long double);
			break;
		case 16:
			va_arg(args, char const*);
			break;
		case 17:
			va_arg(args, void const*);
			break;
		default:
			unreachable();
	}
	return i;
}

static inline bool detail_pl_format_check(char const* sloc_file, size_t sloc_line, char const* format, va_list args) {
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
		if (va_arg(args, int) == 0) {
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
#endif

static inline size_t detail_pl_format_impl(void* buffer, bool is_stream, size_t* size, size_t max_size, char const* format, size_t i, va_list args) {
	char spec[256] = {};
	size_t spec_size = 0;
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
				i = detail_pl_format_impl(spec, false, &spec_size, sizeof(spec), format, i + 1, args);
				continue;
			}
			++i;
		}
		spec[spec_size++] = format[i];
	}
	int pad = (int)strtoll(spec, nullptr, 0);
	#define detail_pl_format_arg(SPEC, ARG) do { \
		if ((*size + !is_stream) < max_size) { \
			if (buffer) { \
				if (is_stream) { \
					*size += (size_t)fprintf(buffer, (SPEC), pad, (ARG)); \
				} else if (~max_size) { \
					*size += (size_t)snprintf((char*)buffer + *size, max_size - *size, (SPEC), pad, (ARG)); \
					if (i >= ~-max_size) { \
						*size = ~-max_size; \
					} \
				} else { \
					*size += (size_t)sprintf((char*)buffer + *size, (SPEC), pad, (ARG)); \
				} \
			} else { \
				*size += (size_t)snprintf(nullptr, 0, (SPEC), pad, (ARG)); \
			} \
		} \
	} while (false)
	switch (va_arg(args, int)) {
		case 1:
		case 2:
			detail_pl_format_arg("%*u", (unsigned int)va_arg(args, int));
			break;
		case 3:
			detail_pl_format_arg("%*u", va_arg(args, unsigned int));
			break;
		case 4:
			detail_pl_format_arg("%*lu", va_arg(args, unsigned long));
			break;
		case 5:
			detail_pl_format_arg("%*llu", va_arg(args, unsigned long long));
			break;
		case 6:
		case 7:
		case 8:
			detail_pl_format_arg("%*i", va_arg(args, int));
			break;
		case 9:
			detail_pl_format_arg("%*li", va_arg(args, long));
			break;
		case 10:
			detail_pl_format_arg("%*lli", va_arg(args, long long));
			break;
		case 11:
		case 12:
			detail_pl_format_arg("%*f", va_arg(args, double));
			break;
		case 13:
			detail_pl_format_arg("%*Lf", va_arg(args, long double));
			break;
		case 14:
			detail_pl_format_arg("%*c", va_arg(args, int));
			break;
		case 15:
			detail_pl_format_arg("%*s", va_arg(args, int) ? "true" : "false");
			break;
		case 16:
			detail_pl_format_arg("%*s", va_arg(args, char const*));
			break;
		case 17:
			detail_pl_format_arg("%*p", va_arg(args, void const*));
			break;
		default:
			unreachable();
	}
	return i;
}

static inline size_t detail_pl_format_to([[maybe_unused]] char const* sloc_file, [[maybe_unused]] size_t sloc_line, void* buffer, bool is_stream, size_t max_size, char const* format, ...) {
	va_list args;
#ifndef NDEBUG
	va_start(args, format);
	if (!detail_pl_format_check(sloc_file, sloc_line, format, args)) {
		abort();
	}
	va_end(args);
#endif
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
	if (!is_stream) {
		((char*)buffer)[size] = '\0';
	}
	va_end(args);
	return size;
}

#endif
