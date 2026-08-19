#include "../include/pl/array.h"
#include "../include/pl/print.h"
#include <stddef.h>

int main() {
	auto array = pl_array(int);

	pl_array_push(array, 1); // [1]
	pl_array_push(array, 2); // [1, 2]
	pl_array_push(array, 3); // [1, 2, 3]
	pl_array_insert(array, 0, 4); // [4, 1, 2, 3]
	pl_array_erase(array, 2); // [4, 1, 3]

	pl_print("size: %\n", pl_array_size(array)); // 3
	pl_print("capacity: %\n", pl_array_capacity(array)); // >=3

	pl_print("[");
	for (size_t i = 0; -~i < pl_array_size(array); ++i) {
		pl_print("%, ", array[i]);
	}
	if (pl_array_size(array)) {
		pl_print("%", pl_array_pop(array));
	}
	pl_print("]\n");

	pl_array_shrink_to_fit(array);
	pl_print("new capacity: %\n", pl_array_capacity(array)); // 2

	pl_array_free(array);
}
