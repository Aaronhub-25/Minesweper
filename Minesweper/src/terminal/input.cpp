#include "input.h"
#include <ncurses.h>
#include <curses.h>

// Static variable to track if ncurses is initialized
static bool ncurses_initialized = false;

// Initialize ncurses for input handling
void init_input() {
    if (!ncurses_initialized) {
        initscr();              // Initialize ncurses
        cbreak();               // Disable line buffering
        noecho();               // Don't echo input characters
        keypad(stdscr, TRUE);   // Enable special keys (arrow keys, function keys, etc.)
        curs_set(0);            // Hide cursor (optional, can be set to 1 to show)
        nodelay(stdscr, FALSE); // Wait for input (set to TRUE for non-blocking)
        ncurses_initialized = true;
    } else {
        // If already initialized, just refresh the screen
        refresh();
    }
}

// Cleanup ncurses
void cleanup_input() {
    if (ncurses_initialized) {
        endwin();               // End ncurses mode
        ncurses_initialized = false;
    }
}

// Get a key press
// Returns key codes from ncurses:
// - KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT for arrow keys
// - Regular ASCII codes for normal keys
// - Special keys like KEY_ENTER, KEY_BACKSPACE, etc.
int get_key() {
    return getch();
}