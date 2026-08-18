#include "../include/pl/sleep.h"
#include <stddef.h>
#include <stdio.h>

int main() {
	char message[] = "Hello, world!\n";
	for (size_t i = 0; i < sizeof(message); ++i) {
		fflush(stdout);
		pl_sleep(100);
		putchar(message[i]);
	}
}
