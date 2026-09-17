#include <pl/print.h>
#include <pl/sleep.h>
#include <pl/term.h>
#include <stddef.h>
#include <stdio.h>

int main() {
	pl_term_save_screen();
	pl_term_hide_cursor();
	pl_term_set_echo(false);
	pl_term_set_canonical(false);

	for (unsigned long long frame = 0; pl_term_read() == EOF; ++frame) {
		pl_term_clear();

		pl_term_set_fg(0xFF00FF);
		pl_print("frame: {}", frame);
		pl_term_reset_style();

		pl_term_pos_t size = pl_term_size();
		char line1[64] = {};
		size_t length1 = pl_format_to(line1, "size: {}x{}", size.row, size.col);
		pl_term_set_pos(size.row / 2, -~size.col / 2 - -~length1 / 2);
		pl_term_set_fg(0xFF0000);
		pl_print("{}", line1);
		pl_term_reset_style();

		char line2[] = " press any key to exit ";
		pl_term_set_pos(size.row / 2 + 1, -~size.col / 2 - -~sizeof(line2) / 2);
		pl_term_set_fg(0x000000);
		pl_term_set_bg(0xFF0000);
		pl_term_set_bold(true);
		pl_print("{}", line2);
		pl_term_reset_style();

		fflush(stdout);
		pl_sleep(10);
	}

	pl_term_set_canonical(true);
	pl_term_set_echo(true);
	pl_term_show_cursor();
	pl_term_restore_screen();
}
