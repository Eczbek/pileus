#ifndef PL_SWAP_H
#define PL_SWAP_H

#include <stddef.h>
#include <string.h>

// Assigns each variable to the other's value.
// If the variables have different types, each is cast to the other's type before assignment.
#define pl_swap(A, B) \
	((void)_Generic(typeof_unqual(A), typeof_unqual(B): pl_swap(true, sizeof(A), &(A), &(B), &(unsigned char[sizeof(A)]){}), default: _Generic(typeof_unqual(A), typeof_unqual(B): (int){}, default: (A)) = (typeof(_Generic(typeof_unqual(A), typeof_unqual(B): 0, default: (A)))){ (typeof(_Generic(typeof_unqual(A), typeof_unqual(B): 0, default: (A))))*(typeof(_Generic(typeof_unqual(A), typeof_unqual(B): 0, default: (B)))*)pl_swap(false, sizeof(B), &(B), &(typeof(_Generic(typeof_unqual(A), typeof_unqual(B): 0, default: (B)))){ (typeof(_Generic(typeof_unqual(A), typeof_unqual(B): 0, default: (B))))(_Generic(typeof_unqual(A), typeof_unqual(B): 0, default: (A))) }, &(unsigned char[sizeof(B)]){}) }))
static inline void* (pl_swap)(bool same_type, size_t size, void* lhs, void* rhs, void* buf) {
	memcpy(buf, lhs, size);
	memcpy(lhs, rhs, size);
	if (same_type) {
		memcpy(rhs, buf, size);
	}
	return buf;
}

#endif
