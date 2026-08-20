#include "../include/pl/print.h"

int main() {
	pl_print("Hello, /%%!\n", 42); // Hello, %42!
	pl_print("% %", 1);
	pl_print("%", 1, 2);
	pl_print("%", (int*)0);
}
