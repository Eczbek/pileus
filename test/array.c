#include "../include/pl/array.h"
#include <stddef.h>
#include <stdio.h>

int main() {
	auto array = pl_array(int);

	pl_array_push(array, 1); // [1]
	pl_array_push(array, 2); // [1, 2]
	pl_array_push(array, 3); // [1, 2, 3]
	pl_array_insert(array, 0, 4); // [4, 1, 2, 3]
	pl_array_erase(array, 2); // [4, 1, 3]

	printf("size: %zu\n", pl_array_size(array)); // 3
	printf("capacity: %zu\n", pl_array_capacity(array)); // >=3

	printf("[");
	for (size_t i = 0; -~i < pl_array_size(array); ++i) {
		printf("%i, ", array[i]);
	}
	if (pl_array_size(array)) {
		printf("%i", pl_array_pop(array));
	}
	printf("]\n");

	pl_array_shrink_to_fit(array);
	printf("new capacity: %zu\n", pl_array_capacity(array)); // 2

	pl_array_free(array);
}
