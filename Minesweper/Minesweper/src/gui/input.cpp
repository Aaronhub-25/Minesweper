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
        nodelay(stdscr, TRUE);  // Ist an um fps selber zu managen
        
        // Initialize colors if terminal supports it
        if (has_colors()) {
            start_color();
            // Define color pairs: init_pair(pair_number, foreground, background)
            init_pair(1, COLOR_GREEN, COLOR_BLACK);      // Number 1 - Grün
            init_pair(2, COLOR_YELLOW, COLOR_BLACK);     // Number 2 - Gelb
            init_pair(3, COLOR_YELLOW, COLOR_BLACK);     // Number 3 - Orange (YELLOW als Näherung)
            init_pair(4, COLOR_RED, COLOR_BLACK);        // Number 4 - Rot
            init_pair(5, COLOR_RED, COLOR_BLACK);        // Number 5 - Dunkelrot (RED)
            init_pair(6, COLOR_CYAN, COLOR_BLACK);       // Number 6
            init_pair(7, COLOR_WHITE, COLOR_BLACK);      // Number 7
            init_pair(8, COLOR_BLACK, COLOR_BLACK);      // Number 8
            init_pair(9, COLOR_RED, COLOR_BLACK);        // Flag - Rot
            init_pair(10, COLOR_MAGENTA, COLOR_BLACK);   // Mine - Magenta (damit es sich von Rot unterscheidet)
        }
        
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