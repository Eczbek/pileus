#include "../include/pl/swap.h"
#include <stdio.h>

typedef struct {
	int x;
	char y;
} A;

int main() {
	int x = 1;
	double y = 2.0;
	pl_swap(x, y);
	printf("%i <-> %f\n", x, y);

	A a = { 1, 2 };
	A b = { 3, 4 };
	pl_swap(a, b);
	printf("(%i, %i) <-> (%i, %i)\n", a.x, a.y, b.x, b.y);
}
