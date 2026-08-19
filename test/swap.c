#include "../include/pl/print.h"
#include "../include/pl/swap.h"

typedef struct {
	int x;
	char y;
} A;

int main() {
	int x = 1;
	double y = 2.0;
	pl_swap(x, y);
	pl_print("% <-> %\n", x, y);

	A a = { 1, '2' };
	A b = { 3, '4' };
	pl_swap(a, b);
	pl_print("(%, %) <-> (%, %)\n", a.x, a.y, b.x, b.y);
}
