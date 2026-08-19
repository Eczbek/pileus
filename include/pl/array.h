#ifndef PL_ARRAY_H
#define PL_ARRAY_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Accepts a type and an optional size_t expression representing the initial capacity of the array.
// Evaluates to a pointer to the body of a newly allocated array.
// Must be deallocated by pl_array_free().
#define pl_array(item_type, ...) \
	((item_type*)pl_array(sizeof(item_type), __VA_OPT__(true ? (__VA_ARGS__) :) (64 / sizeof(item_type)) | (64 < sizeof(item_type))))
static inline void* (pl_array)(size_t item_size, size_t capacity) {
	if (size_t* array = malloc(sizeof(size_t) * 2 + item_size * capacity)) {
		array[0] = 0;
		array[1] = capacity;
		return array + 2;
	}
	return nullptr;
}

// Accepts the identifier of an array created by pl_array().
// Deallocates the array.
#define pl_array_free(array) \
	(free((size_t*)(array) - 2))

// Accepts the identifier of an array created by pl_array().
// Evaluates to a size_t expression representing the number of elements in the array.
#define pl_array_size(array) \
	(*((const size_t*)(array) - 2))

// Accepts the identifier of an array created by pl_array().
// Evaluates to a size_t expression representing the number of elements the array has capacity for.
#define pl_array_capacity(array) \
	(*((const size_t*)(array) - 1))

// Accepts the identifier of an array created by pl_array() and a size_t expression representing additional size.
// If the sum of the array's size and additional size is greater than the array's capacity, reallocates the array such that its capacity is not less than said sum.
#define pl_array_reserve(array, ...) \
	((array) = pl_array_reserve((array), sizeof*(array), (__VA_ARGS__)))
static inline void* (pl_array_reserve)(void* array, size_t item_size, size_t additional_size) {
	if (size_t target_capacity = pl_array_size(array) + additional_size; target_capacity > pl_array_capacity(array)) {
		size_t new_capacity = pl_array_capacity(array);
		do {
			new_capacity += new_capacity / 2;
		} while (target_capacity > new_capacity);
		if (size_t* new_array = (pl_array)(item_size, new_capacity)) {
			memcpy(new_array, array, item_size * pl_array_capacity(array));
			*(new_array - 2) = pl_array_size(array);
			*(new_array - 1) = new_capacity;
			pl_array_free(array);
			return new_array;
		}
	}
	return array;
}

// Accepts the identifier of an array created by pl_array().
// Reallocates the array such that its capacity matches its size.
#define pl_array_shrink_to_fit(array) \
	((array) = pl_array_shrink_to_fit((array), sizeof*(array)))
static inline void* (pl_array_shrink_to_fit)(void* array, size_t item_size) {
	if (size_t* new_array = (pl_array)(item_size, pl_array_size(array))) {
		memcpy(new_array, array, item_size * pl_array_size(array));
		*(new_array - 2) = pl_array_size(array);
		pl_array_free(array);
		return new_array;
	}
	return array;
}

// Accepts the identifier of an array created by pl_array(), a size_t expression representing an index in the array, and an expression to construct a new element at said index.
// Reallocates the array if the its size is not less than its capacity.
// If the index is less than the array's size, moves back every element after the index and inserts the new element at the index.
#define pl_array_insert(array, index, ...) \
	((array) = pl_array_insert((array), sizeof*(array), (index), &(typeof(__VA_ARGS__)){ (__VA_ARGS__) }))
static inline void* (pl_array_insert)(void* array, size_t item_size, size_t index, void* value) {
	if ((index <= pl_array_size(array)) && (array = (pl_array_reserve)(array, item_size, 1))) {
		for (size_t i = ++*((size_t*)array - 2); --i > index;) {
			memcpy((unsigned char*)array + i * item_size, (unsigned char*)array + ~-i * item_size, item_size);
		}
		memcpy((unsigned char*)array + index * item_size, value, item_size);
	}
	return array;
}

// Accepts the identifier of an array created by pl_array() and an expression to construct a new element at the end of the array.
// Reallocates the array if its size is not less than its capacity.
// Appends the new element to the array.
#define pl_array_push(array, ...) \
	(pl_array_insert((array), pl_array_size(array), __VA_ARGS__))

// Accepts the identifier of an array created by pl_array() and a size_t expression representing an index in the array.
// If the index is less than the array's size, removes the element at the index and moves forward every element after the index.
#define pl_array_erase(array, ...) \
	(pl_array_erase((array), sizeof*(array), (__VA_ARGS__)))
static inline void (pl_array_erase)(void* array, size_t item_size, size_t index) {
	*((size_t*)array - 2) -= (index < pl_array_size(array));
	while (index++ < pl_array_size(array)) {
		memcpy((unsigned char*)array + ~-index * item_size, (unsigned char*)array + index * item_size, item_size);
	}
}

// Accepts the identifier of an array created by pl_array().
// Removes and returns the last element in the array.
#define pl_array_pop(array) \
	((array)[--*((size_t*)(array) - 2)])

#endif
