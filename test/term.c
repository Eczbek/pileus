#include "../include/pl/sleep.h"
#include "../include/pl/term.h"
#include <stdio.h>
#include <string.h>

int main() {
	pl_term_save_screen();
	pl_term_hide_cursor();
	pl_term_set_echoing(false);
	pl_term_set_canonical(false);

	for (unsigned long long frame = 0; pl_term_input() == EOF; ++frame) {
		pl_term_clear();

		pl_term_set_fg(0xFF00FF);
		printf("frame: %llu", frame);
		pl_term_reset_style();

		pl_term_pos_t size = pl_term_size();
		char line1[64] = {};
		sprintf(line1, "size: %zux%zu", size.row, size.col);
		pl_term_set_pos(size.row / 2, -~size.col / 2 - -~strlen(line1) / 2);
		pl_term_set_fg(0xFF0000);
		printf("%s", line1);
		pl_term_reset_style();

		char line2[] = "press any key to exit";
		pl_term_set_pos(size.row / 2 + 1, -~size.col / 2 - -~sizeof(line2) / 2);
		pl_term_set_fg(0x000000);
		pl_term_set_bg(0xFF0000);
		pl_term_set_bold(true);
		printf("%s", line2);
		pl_term_reset_style();

		fflush(stdout);
		pl_sleep(10);
	}

	pl_term_set_canonical(true);
	pl_term_set_echoing(true);
	pl_term_show_cursor();
	pl_term_restore_screen();
}
