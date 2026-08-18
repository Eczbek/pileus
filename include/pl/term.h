#ifndef PL_TERM_H
#define PL_TERM_H

#include "./meta.h"
#include "./warn.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __unix__
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#elifdef _WIN32
#include <conio.h>
#include <Windows.h>
#else
#warning platform does not provide terminal mode functions
#endif

static inline void pl_term_clear() {
	printf("\x1B[2J\x1B[3J\x1B[H");
}

static inline void pl_term_reset_style() {
	printf("\x1B[0m");
}

static inline void pl_term_save_screen() {
	printf("\x1B[?47h\x1B[s");
}

static inline void pl_term_restore_screen() {
	printf("\x1B[u\x1B[?47l");
}

static inline void pl_term_hide_cursor() {
	printf("\x1B[?25l");
}

static inline void pl_term_show_cursor() {
	printf("\x1B[?25h");
}

typedef struct {
	uint_least8_t r;
	uint_least8_t g;
	uint_least8_t b;
} pl_term_color_t;

#define pl_term_color(...) \
	pl_term_color((uint_least32_t)(__VA_ARGS__))
static inline pl_term_color_t (pl_term_color)(uint_least32_t x) {
	return (pl_term_color_t){ (x >> 16) & 0xFF, (x >> 8) & 0xFF, x & 0xFF };
}

#define pl_term_set_fg(...) \
	(pl_choose(pl_is_int(__VA_ARGS__), pl_term_set_fg, detail_pl_term_fg)(__VA_ARGS__))
static inline void detail_pl_term_fg(pl_term_color_t color) {
	printf("\x1B[38;2;%i;%i;%im", color.r, color.g, color.b);
}
static inline void (pl_term_set_fg)(uint_least32_t fg) {
	detail_pl_term_fg(pl_term_color(fg));
}

#define pl_term_set_bg(...) \
	(pl_choose(pl_is_int(__VA_ARGS__), pl_term_set_bg, detail_pl_term_bg)(__VA_ARGS__))
static inline void detail_pl_term_bg(pl_term_color_t color) {
	printf("\x1B[48;2;%i;%i;%im", color.r, color.g, color.b);
}
static inline void (pl_term_set_bg)(uint_least32_t fg) {
	detail_pl_term_bg(pl_term_color(fg));
}

static inline void pl_term_set_bold(bool option) {
	printf("\x1B[%im", option ? 1 : 22);
}

static inline void pl_term_set_italic(bool option) {
	printf("\x1B[%im", option ? 3 : 23);
}

static inline void pl_term_set_underline(bool option) {
	printf("\x1B[%im", option ? 4 : 24);
}

static inline void pl_term_set_blinking(bool option) {
	printf("\x1B[%im", option ? 5 : 25);
}

static inline void pl_term_set_strikethrough(bool option) {
	printf("\x1B[%im", option ? 9 : 29);
}

static inline bool pl_term_echoing() {
#ifdef __unix__
	struct termios mode;
	tcgetattr(STDIN_FILENO, &mode);
	return mode.c_lflag & (tcflag_t)ECHO;
#elifdef _WIN32
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
	return mode & ENABLE_ECHO_INPUT;
#else
	return false;
#endif
}

static inline void pl_term_set_echoing([[maybe_unused]] bool option) {
#ifdef __unix__
	struct termios mode;
	tcgetattr(STDIN_FILENO, &mode);
	mode.c_lflag ^= ((tcflag_t)-option ^ mode.c_lflag) & (tcflag_t)ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &mode);
#elifdef _WIN32
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(handle, &mode);
	SetConsoleMode(handle, option ? (mode | ENABLE_ECHO_INPUT) : (mode & ~ENABLE_ECHO_INPUT));
#endif
}

static inline bool pl_term_canonical() {
#ifdef __unix__
	struct termios mode;
	tcgetattr(STDIN_FILENO, &mode);
	return mode.c_lflag & (tcflag_t)ICANON;
#elifdef _WIN32
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
	return mode & ENABLE_LINE_INPUT;
#else
	return false;
#endif
}

static inline void pl_term_set_canonical([[maybe_unused]] bool option) {
#ifdef __unix__
	struct termios mode;
	tcgetattr(STDIN_FILENO, &mode);
	mode.c_lflag ^= ((tcflag_t)-option ^ mode.c_lflag) & (tcflag_t)ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &mode);
#elifdef _WIN32
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(handle, &mode);
	SetConsoleMode(handle, option ? (mode | ENABLE_LINE_INPUT) : (mode & ~ENABLE_LINE_INPUT));
#endif
}

static inline bool pl_term_signaling() {
#ifdef __unix__
	struct termios mode;
	tcgetattr(STDIN_FILENO, &mode);
	return (mode.c_iflag & (tcflag_t)(ICRNL | IXON))
		|| (mode.c_lflag & (tcflag_t)(IEXTEN | ISIG));
#elifdef _WIN32
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
	return mode & ENABLE_PROCESSED_INPUT;
#else
	return false;
#endif
}

static inline void pl_term_set_signaling([[maybe_unused]] bool option) {
#ifdef __unix__
	struct termios mode;
	tcgetattr(STDIN_FILENO, &mode);
	mode.c_iflag ^= ((tcflag_t)-option ^ mode.c_iflag) & (tcflag_t)(ICRNL | IXON);
	mode.c_lflag ^= ((tcflag_t)-option ^ mode.c_lflag) & (tcflag_t)(IEXTEN | ISIG);
	tcsetattr(STDIN_FILENO, TCSANOW, &mode);
#elifdef _WIN32
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(handle, &mode);
	SetConsoleMode(handle, option ? (mode | ENABLE_PROCESSED_INPUT) : (mode & ~ENABLE_PROCESSED_INPUT));
#endif
}

static inline bool pl_term_postprocessing() {
#ifdef __unix__
	struct termios mode;
	tcgetattr(STDIN_FILENO, &mode);
	return mode.c_oflag & (tcflag_t)OPOST;
#elifdef _WIN32
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
	return mode & ENABLE_PROCESSED_OUTPUT;
#else
	return false;
#endif
}

static inline void pl_term_set_postprocessing([[maybe_unused]] bool option) {
#ifdef __unix__
	struct termios mode;
	tcgetattr(STDIN_FILENO, &mode);
	mode.c_oflag ^= ((tcflag_t)-option ^ mode.c_oflag) & (tcflag_t)OPOST;
	tcsetattr(STDIN_FILENO, TCSANOW, &mode);
#elifdef _WIN32
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(handle, &mode);
	SetConsoleMode(handle, option ? (mode | ENABLE_PROCESSED_OUTPUT) : (mode & ~ENABLE_PROCESSED_OUTPUT));
#endif
}

typedef struct {
	size_t row;
	size_t col;
} pl_term_pos_t;

static inline pl_term_pos_t pl_term_pos() {
#ifdef __unix__
	bool echo = pl_term_echoing();
	pl_term_set_echoing(false);
	bool canonical = pl_term_canonical();
	pl_term_set_canonical(false);
	printf("\x1B[6n");
	size_t row;
	size_t col;
	scanf("\x1B[%zu;%zuR", &row, &col);
	pl_term_set_echoing(echo);
	pl_term_set_canonical(canonical);
	return (pl_term_pos_t){ ~-row, ~-col };
#elifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) {
		return (term_pos_t){ (size_t)info.dwCursorPosition.Y, (size_t)info.dwCursorPosition.X };
	}
#endif
	return (pl_term_pos_t){ (size_t)-1, (size_t)-1 };
}

#define pl_term_set_pos(...) \
	pl_ignore_unused((pl_choose(pl_is_int(__VA_ARGS__), pl_term_set_pos, detail_pl_term_set_pos)(__VA_ARGS__)))
static inline void (pl_term_set_pos)(size_t row, size_t col) {
	printf("\x1B[%zu;%zuH", -~row, -~col);
}
static inline void detail_pl_term_set_pos(pl_term_pos_t pos) {
	(pl_term_set_pos)(pos.row, pos.col);
}

static inline pl_term_pos_t pl_term_size() {
#ifdef __unix
	struct winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	return (pl_term_pos_t){ size.ws_row, size.ws_col };
#elifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) {
		return (pl_term_pos_t){ (size_t)(info.srWindow.Bottom - info.srWindow.Top), (size_t)(info.srWindow.Right - info.srWindow.Left) };
	}
#endif
	return (pl_term_pos_t){ (size_t)-1, (size_t)-1 };
}

static inline int pl_term_input() {
#ifdef __unix__
	int mode = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, mode | O_NONBLOCK);
	int input = getchar();
	fcntl(STDIN_FILENO, F_SETFL, mode);
	return input;
#elifdef _WIN32
	return _kbhit() ? _getch() : EOF;
#else
	return EOF;
#endif
}

#endif
