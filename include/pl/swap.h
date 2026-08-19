#ifndef PL_SWAP_H
#define PL_SWAP_H

#include <stddef.h>
#include <string.h>

// Assigns each variable to the other's value.
// If the variables have different types, each is cast to the other's type before assignment.
#define pl_swap(lhs, rhs) \
	((void)_Generic(typeof_unqual(lhs), typeof_unqual(rhs): pl_swap(true, sizeof(lhs), &(lhs), &(rhs), &(unsigned char[sizeof(lhs)]){}), default: _Generic(typeof_unqual(lhs), typeof_unqual(rhs): (int){}, default: (lhs)) = (typeof(_Generic(typeof_unqual(lhs), typeof_unqual(rhs): 0, default: (lhs)))){ (typeof(_Generic(typeof_unqual(lhs), typeof_unqual(rhs): 0, default: (lhs))))*(typeof(_Generic(typeof_unqual(lhs), typeof_unqual(rhs): 0, default: (rhs)))*)pl_swap(false, sizeof(rhs), &(rhs), &(typeof(_Generic(typeof_unqual(lhs), typeof_unqual(rhs): 0, default: (rhs)))){ (typeof(_Generic(typeof_unqual(lhs), typeof_unqual(rhs): 0, default: (rhs))))(_Generic(typeof_unqual(lhs), typeof_unqual(rhs): 0, default: (lhs))) }, &(unsigned char[sizeof(rhs)]){}) }))
static inline void* (pl_swap)(bool same_type, size_t size, void* lhs, void* rhs, void* tmp) {
	memcpy(tmp, lhs, size);
	memcpy(lhs, rhs, size);
	if (same_type) {
		memcpy(rhs, tmp, size);
	}
	return tmp;
}

#endif
