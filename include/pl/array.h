#ifndef PL_ARRAY_H
#define PL_ARRAY_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Accepts a type, an initial size, and an optional fill value.
// Evaluates to a pointer to the body of the array.
// If allocation fails, returns nullptr.
// Must be deallocated by pl_array_free().
#define pl_array(item_type, size, /*fill_value = {}*/...) ((typeof(item_type)*)(pl_array_resize)((typeof(item_type)*)0,sizeof(item_type),alignof(typeof(item_type)),(size),(typeof(item_type)[1]){__VA_ARGS__}))

// Accepts the identifier of an array created by pl_array().
// Deallocates the array and assigns it to nullptr.
#define pl_array_free(array) ((void)((array)&&(free((size_t*)(void*)(array)-2),(array)=0)))

// Accepts the identifier of an array created by pl_array().
// Evaluates to the size of the array.
#define pl_array_size(array) ((array)?*((const size_t*)(const void*)(array)-2):0)

// Accepts the identifier of an array created by pl_array().
// Evaluates to the capacity of the array.
#define pl_array_capacity(array) ((array)?*((const size_t*)(const void*)(array)-1):0)

// Accepts the identifier of an array created by pl_array() and additional size to acquire capacity for.
// Reallocates the array such that its capacity is not less than the sum of its size and the additional size.
// If allocation fails, the array is unchanged.
#define pl_array_reserve(array, additional_size) ((void)((array)=pl_array_reserve((array),sizeof*(array),alignof(typeof(*(array))),(additional_size))))
static inline void* (pl_array_reserve)(void* array, size_t item_size, size_t item_align, size_t additional_size) {
	if (size_t target_capacity = pl_array_size(array) + additional_size; pl_array_capacity(array) < target_capacity) {
		size_t min_capacity = 64 / item_size;
		size_t new_capacity = (pl_array_capacity(array) < min_capacity) ? min_capacity : pl_array_capacity(array);
		while (new_capacity < target_capacity) {
			if (new_capacity < 2) {
				++new_capacity;
			} else {
				new_capacity += new_capacity / 2;
			}
		}
		size_t max_align = (alignof(size_t) < item_align) ? item_align : alignof(size_t);
		size_t aligned_size = 2 * sizeof(size_t) + new_capacity * item_size;
		if (size_t rem = aligned_size % max_align) {
			aligned_size += max_align - rem;
		}
		if (size_t* new_array = aligned_alloc(max_align, aligned_size)) {
			new_array[0] = pl_array_size(array);
			new_array[1] = new_capacity;
			if (array) {
				memcpy(new_array + 2, array, item_size * pl_array_size(array));
				pl_array_free(array);
			}
			return ((2 * sizeof(size_t)) < max_align) ? ((unsigned char*)new_array + max_align) : (void*)(new_array + 2);
		}
	}
	return array;
}

// Accepts the identifier of an array created by pl_array().
// Reallocates the array such that its capacity matches its size.
// If allocation fails, the array is unchanged.
#define pl_array_shrink_to_fit(array) ((void)((array)=pl_array_shrink_to_fit((array),sizeof*(array),alignof(typeof(*(array))))))
static inline void* (pl_array_shrink_to_fit)(void* array, size_t item_size, size_t item_align) {
	if (!pl_array_size(array)) {
		return nullptr;
	}
	if (pl_array_size(array) < pl_array_capacity(array)) {
		size_t max_align = (alignof(size_t) < item_align) ? item_align : alignof(size_t);
		size_t aligned_size = 2 * sizeof(size_t) + pl_array_size(array) * item_size;
		if (size_t rem = aligned_size % max_align) {
			aligned_size += max_align - rem;
		}
		if (size_t* new_array = aligned_alloc(max_align, aligned_size)) {
			memcpy(new_array + 2, array, item_size * pl_array_size(array));
			new_array[0] = pl_array_size(array);
			new_array[1] = pl_array_size(array);
			pl_array_free(array);
			return ((2 * sizeof(size_t)) < max_align) ? ((unsigned char*)new_array + max_align) : (void*)(new_array + 2);
		}
	}
	return array;
}

// Accepts the identifier of an array created by pl_array(), the target size, and an optional fill value.
// Resizes the array, filling new elements with the given value.
// If allocation fails, the array is unchanged.
#define pl_array_resize(array, size, /*fill_value = {}*/...) ((void)((array) = pl_array_resize((array),sizeof*(array),alignof(typeof(*(array))),(size),(typeof(*(array))[1]){__VA_ARGS__})))
static inline void* (pl_array_resize)(void* array, size_t item_size, size_t item_align, size_t target_size, void* fill_value) {
	if (pl_array_size(array) < target_size) {
		array = (pl_array_reserve)(array, item_size, item_align, target_size - pl_array_size(array));
	}
	if (array && (target_size <= pl_array_capacity(array))) {
		for (size_t i = pl_array_size(array); i < target_size; ++i) {
			memcpy((unsigned char*)array + i * item_size, fill_value, item_size);
		}
	}
	return array;
}

// Accepts the identifier of an array created by pl_array(), an index in the array, and an element to insert.
// Reallocates the array if the its size is not less than its capacity.
// If the index is less than the array's size, moves back every element after the index and inserts the new element at the index.
// If allocation fails, the array is unchanged.
#define pl_array_insert(array, index, /*value = {}*/...) ((void)((array)=pl_array_insert((array),sizeof*(array),alignof(typeof(*(array))),(index),(typeof(*(array))[1]){__VA_ARGS__})))
static inline void* (pl_array_insert)(void* array, size_t item_size, size_t item_align, size_t index, void* value) {
	if (index <= pl_array_size(array)) {
		array = (pl_array_reserve)(array, item_size, item_align, 1);
		if (pl_array_size(array) < pl_array_capacity(array)) {
			for (size_t i = ++*((size_t*)array - 2); --i > index;) {
				memcpy((unsigned char*)array + i * item_size, (unsigned char*)array + ~-i * item_size, item_size);
			}
			memcpy((unsigned char*)array + index * item_size, value, item_size);
		}
	}
	return array;
}

// Accepts the identifier of an array created by pl_array() and an element to append to the end of the array.
// Reallocates the array if its size is not less than its capacity.
// If allocation fails, the array is unchanged.
#define pl_array_append(array, /*value = {}*/...) pl_array_insert((array),pl_array_size(array),__VA_ARGS__)

// Accepts the identifier of an array created by pl_array(), an index in the array, and an optional number of elements to remove.
// Removes elements starting at the index and moves forward every remaining element after the last removed element.
#define pl_array_erase(array, index, /*count = 1*/...) pl_array_erase((array),sizeof*(array),(index),__VA_OPT__(1?(__VA_ARGS__):)1)
static inline void (pl_array_erase)(void* array, size_t item_size, size_t index, size_t count) {
	if (index < pl_array_size(array)) {
		if ((pl_array_size(array) - index) < count) {
			count = pl_array_size(array) - index;
		}
		*((size_t*)array - 2) -= count;
		memmove((unsigned char*)array + index * item_size, (unsigned char*)array + (index + count) * item_size, count * item_size);
	}
}

// Accepts the identifier of a non-empty array created by pl_array().
// Removes and returns the last element in the array.
#define pl_array_pop(array) ((array)[--*((size_t*)(void*)(array)-2)])

#endif
